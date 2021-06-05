
#ifndef AnalyzeHelper_h
#define AnalyzeHelper_h

#include "ClusterOfSets.h"
// #include "synHelper.h"
#include <set>
using namespace std;

class AnalyzeHelper{
private:
    map<Symbol, set<Symbol>> first;     // symbol对应于文法符号，set<symbol>为对应的first集合
    // 终结符
    set<Symbol> Vt;                     
    // 非终结符
    set<Symbol> Vn;                  
    // 所有产生式
    SetOfItems productions;             
    
    void calcAllFirst(){

        // 若 x in Vt first(x) ={x}
        for(auto& vt:Vt){
            set<Symbol> s;
            s.insert(vt);
            first[vt] = s;
        }
        // 若 x in Vn,有产生式 x->a.. ;a in Vt,则把a 加入
        for(auto& vn: Vn){
            first[vn] = set<Symbol>();

            for(auto& it:productions.getVitems()){
                Symbol rightFirst = it.getRightSide()[0];
                // 对于形如X->a...
                if(vn == it.getLeftSide() && rightFirst.getType()==TERMINAL){
                    // 加入到first集
                    first[vn].insert(rightFirst);
                }
            }
        }

        // 如果first集发生变化，则一直循环，直到没有更新
        bool isFirstChanging = true;
        while (isFirstChanging) {
            isFirstChanging = false;
            // 对于每一个非终结符和每一个产生式，进行first集的分析
            for(auto& vn : Vn){
                for(auto& it : productions.getVitems()){
                    Symbol rightFirst = it.getRightSide()[0];
                    // 产生式右边第一个为非终结符,加入该非终结符的FIRST集
                    if(vn == it.getLeftSide() && rightFirst.getType()==NONTERMINAL){
                        // 遍历该非终结符的first集
                        for(auto& vt : first[rightFirst]){
                            // 当在vn对应的first集中不存在该终结符(vt)时，则加入
                            if(!first[vn].count(vt)){
                                first[vn].insert(vt);
                                isFirstChanging = true;
                            }
                        }
                        // X->Y1Y2Y3... 若有Y1->空集,则加入FIRST(Y2)
                        Symbol null = Symbol(TERMINAL, -1, "null");
                        for(int i=0;i<it.getRightSide().size()-1;i++){
                            // 当前字符
                            Symbol sym = it.getRightSide()[i];
                            if(!first[sym].count(null))
                                break;
                            // 如果当前字符first集包含空集， 则将下一个字符的first集加入进来
                            Symbol next = it.getRightSide()[i+1];
                            for(auto& vt : first[next]){
                                if(!first[vn].count(vt)){
                                    first[vn].insert(vt);
                                    isFirstChanging = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
public:
    AnalyzeHelper(set<Symbol> Vt, set<Symbol> Vn, SetOfItems productions){
        this->Vt = Vt;
        this->Vn = Vn;
        this->productions = productions;
        // 初始化FIRST集
        calcAllFirst();
    }
    map<Symbol, set<Symbol>> getFirstSet() const {
        return first;
    }

    set<Symbol> calcFirst(vector<Symbol> v){
        set<Symbol> firstRes;
        Symbol firstOfv = v[0];
        Symbol null = Symbol(TERMINAL, -1, "null");
        // if x in Vt first(x).append(x)
        if(firstOfv.getType() == TERMINAL){
            firstRes.insert(firstOfv);
            return firstRes;
        }
        // for X->a... a in 
        for(auto vt: first[firstOfv]){
            // 当在firstOfv对应的first集中不存在该终结符(vt)时，则加入
            if(!firstRes.count(vt))     firstRes.insert(vt);
            
        }
        //  if X->Y1Y2Y3... Y1->null
        for(int i=0;i<v.size()-1;i++){
            Symbol cur = v[i];
            if(!first[cur].count(null))     break;
            // X->Y Y in Vn
            Symbol next = v[i+1];
            for(auto& vt : first[next]){
                if(!firstRes.count(vt)){
                    firstRes.insert(vt);
                }
            }
        }
        return firstRes;
    }
    // // 计算除开空集的First集合
    // set<Symbol> calcFirst(vector<Symbol> v){
    //     set<Symbol> firstRes;
    //     Symbol firstOfv = v[0];
    //     Symbol null = Symbol(TERMINAL, -1, "null");
    //     // if x in Vt first(x).append(x)
    //     if(firstOfv.getType() == TERMINAL){
    //         firstRes.insert(firstOfv);
    //         // firstRes.erase(null);
    //         return firstRes;
    //     }
    //     // for X->a...
    //     for(auto vt: first[firstOfv]){
    //         // 当在firstOfv对应的first集中不存在该终结符(vt)时，则加入
    //         if(!firstRes.count(vt)){
    //             firstRes.insert(vt);
    //         }
    //     }
    //     //  if X->Y1Y2Y3... 若有Y1->空集,则加入FIRST(Y2)
    //     for(int i=0;i<v.size()-1;i++){
    //         Symbol cur = v[i];
    //         if(!first[cur].count(null))
    //             break;
    //         // X->Y Y in Vn
    //         Symbol next = v[i+1];
    //         for(auto& vt : first[next]){
    //             if(!firstRes.count(vt)){
    //                 firstRes.insert(vt);
    //             }
    //         }
    //     }
    //     // 去掉空集
    //     // firstRes.erase(null);
    //     return firstRes;
    // }
    /* 计算一个项目集的闭包 */
    SetOfItems closure(SetOfItems soi, SetOfItems productions){
        SetOfItems res = soi;
        vector<Item> proV = productions.getVitems();
        bool isResChanging = true;
        while (isResChanging) {
            vector<Item> vi = res.getVitems();
            isResChanging = false;
            
            for(auto it : vi){
                // it: A -> alpha .B beta, a
                if(it.isReductionItem())
                    continue;
                Symbol B = it.symbolAfterDot();
                vector<Symbol> beta = it.symbolsAfterTheSymbolAfterDot();
                if(B.getType() == TERMINAL || B.getType() == INVALID)
                    continue;
                // 遍历所有产生式，将左边是nextS的产生式加入进来
                for(auto proIt : proV){
                    if(B == proIt.getLeftSide()){
                        // 当beta为空时
                        Item newItem;
                        if(beta.size() == 0){
                            newItem = Item(proIt.getLeftSide(), proIt.getRightSide(), it.getAhead());
                            if(!res.existItem(newItem)){
                                res.appendItem(newItem);
                                isResChanging = true;
                            }
                        }
                        else{
                            Symbol fsOfBeta = beta[0];
                            // 当后面直接是终结符时
                            if(fsOfBeta.getType() == TERMINAL){
                                newItem = Item(proIt.getLeftSide(), proIt.getRightSide(), fsOfBeta);
                                if(!res.existItem(newItem)){
                                    res.appendItem(newItem);
                                    isResChanging = true;
                                }
                            }
                            else if(fsOfBeta.getType() == NONTERMINAL){
                                // 将a压入vector
                                // 求FIRST(beta a)
                                beta.push_back(it.getAhead());
                                set<Symbol> firstSetOfBeta = calcFirst(beta);
                                for(auto f:firstSetOfBeta){
                                    // 当为空集时，不加入进来
                                    if(f == Symbol()) continue;
                                    newItem = Item(proIt.getLeftSide(), proIt.getRightSide(), f, 0);
                                    if(!res.existItem(newItem)){
                                        res.appendItem(newItem);
                                        isResChanging = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return res;
    }
    
    // 计算go（I，X) = closure(J)

    SetOfItems calcGoto(SetOfItems I, Symbol X){
        SetOfItems J = SetOfItems();
        for(auto it : I.getVitems()){
            if(!it.isReductionItem()){
                Symbol s = it.symbolAfterDot();
                if(s == X){
                    Item next = it.nextItem();
                    J.appendItem(next);
                }
            }
        }
        return closure(J, productions);
    }
    
    ClusterOfSets calcCluster(SetOfItems initialSet){
        // C = { closure({ [S'-> .S, $] }) }
        ClusterOfSets C = ClusterOfSets();
        SetOfItems I0 = closure(initialSet, productions);
        C.appendItemSet(I0);
        // 所有文法符合的集合
        set<Symbol> allSymbols;
        allSymbols.insert(Vt.begin(), Vt.end());
        allSymbols.insert(Vn.begin(), Vn.end());
        
        // 对于C中的每一个项目集I和每一个文法符号X，将go(I,X)加入进来，直到没有更新
        bool isClusterChanging = true;
        vector<SetOfItems> allSet;
        while(isClusterChanging){
            isClusterChanging = false;
            allSet = C.getAllSets();
            for(auto I : allSet){
                // cout<<allSet.size()<<endl;
                cout<<"ClusterOfSet is creating and it is NO: "<<allSet.size()<<endl;
                for(auto X : allSymbols){
                    SetOfItems goIX = calcGoto(I, X);
                    if(goIX.size() == 0) continue;
                    // 不存在才加入
                    if(!C.existSet(goIX)){
                        C.appendItemSet(goIX);
                        isClusterChanging = true;
                        // 更新goto表
                        if(!C.isVisitGoto(I.getID(), X)){
//                            cout<<I.getID()<<" "<<X<<" "<<goIX.getID()<<endl;
                            C.updateGoto(I.getID(), X, goIX.getID());

                        }
                        
                    }
                    // 存在也要考虑更新goto表
                    else{
                        // 先搜索对应的下标，因为goIX的ID是随机的，不可使用
                        int setID = C.searchSet(goIX);
                        if(!C.isVisitGoto(I.getID(), X)){
//                            cout<<I.getID()<<" "<<X<<" "<<setID<<endl;
                            C.updateGoto(I.getID(), X, setID);
                        }
                    }
                    
                }
            }
            cout<<isClusterChanging<<endl;
        }
        return C;
    }
};

#endif
