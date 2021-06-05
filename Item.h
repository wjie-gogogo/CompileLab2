
#ifndef Item_h
#define Item_h
#include "Symbol.h"
#include <vector>
#define TERMINAL 0
#define NONTERMINAL 1
#define NOTHING -1

using namespace std;
/*
 * 项目/产生式
 * 上下文无关文法：左边只有一个非终结符，右边是终结符或者非终结符的集合
 * 形如：A -> .alpha beta
 */
class Item{
private:
    Symbol leftSide;
    vector<Symbol> rightSide;
    Symbol ahead;
    int dotPos;     // position of dot  [0,n] , n为rightSide的长度
    int iid;        // id为项目在某一个项目集中的编号

public:
    Item(Symbol left, vector<Symbol> right, Symbol lookAhead, int dot_postion=0, int item_id=0){
        leftSide = left;
        rightSide = right;
        ahead = lookAhead;
        dotPos = dot_postion;
        iid = item_id;
    }
    Item(){
        dotPos = -1;
    }
    Symbol getLeftSide() const { return leftSide; }
    vector<Symbol> getRightSide() const { return rightSide; }
    Symbol getAhead() const { return ahead; }
    int getDotPos() const { return dotPos; }
    
    void setLeftSide(Symbol left){
        leftSide = left;
    }
    void setRightSide(vector<Symbol> right){
        rightSide = right;
    }
    void rightAppend(Symbol s){
        rightSide.push_back(s);
    }
    void setAhead(Symbol s){
        ahead = s;
    }
    void setDotPos(int pos){
        dotPos = pos;
    }
    void setID(int item_id){
        iid = item_id;
    }
    
    Symbol symbolAfterDot() const {
        if(dotPos >= rightSide.size()) return Symbol();  // 返回非法字符
        return rightSide[dotPos];
    }
    
    vector<Symbol> symbolsAfterTheSymbolAfterDot() const {
        vector<Symbol> res;
        res.clear();
        for(int i=dotPos+1;i<rightSide.size();i++){
            res.push_back(rightSide[i]);
        }
        return res;
    }

    // 判断是否为规约项目
    bool isReductionItem(){
        int pos = dotPos;
        // 空集忽略
        Symbol null = Symbol(TERMINAL, -1, "null");
        while(rightSide[pos] == null){
            pos++;
        }
        return pos == rightSide.size();
    }
    
    Item nextItem(){
        // if(isReductionItem())
        //     assert("无法后移\n");
        Item next = Item(leftSide, rightSide, ahead, dotPos+1);
        return next;
    }
    
    // 只看产生式，不看ahead和id
    bool equal(Item& item) const{
        if(leftSide != item.getLeftSide() || rightSide.size() != item.getRightSide().size())
            return false;
        for(int i=0;i<rightSide.size();i++){
            if(rightSide[i] != item.getRightSide()[i])
                return false;
        }
        return true;
    }
    bool operator==(const Item& item) const {
        // iid 只是在项目集中的编号，并不用比较
        if(leftSide==item.getLeftSide() 
        && ahead==item.getAhead() 
        && dotPos==item.getDotPos()){
            if(rightSide.size() != item.getRightSide().size())
                return false;
            for(int i=0;i<rightSide.size();i++){
                if(rightSide[i] != item.getRightSide()[i])
                    return false;
            }
            return true;
        }
        return false;
    }
    friend ostream& operator<<(ostream& os, const Item& it){
        os << it.getLeftSide();
        os << " -> ";
        vector<Symbol> v = it.getRightSide();
        for(int i=0;i<v.size();i++){
            if(it.getDotPos() == i){
                os << " . ";
            }
            os << v[i];
        }
        if(it.getDotPos() == v.size()){
            os << " . ";
        }
        os << ", ";
        os << it.getAhead();
        return os;
    }
};
#endif