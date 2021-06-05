#ifndef Symbol_h
#define Symbol_h
#include <iostream>
#include <vector>

#include <set>
#include <map>
#include <string>
#include "assert.h"
using namespace std;

#define TERMINAL 0
#define NONTERMINAL 1
#define INVALID -1

/*
 * 符号类定义
 */
class Symbol{
private:
    int type;           // terminal or nonterminal or invalid(包括空集）
    int sid;            // define by yourself（特别的，-1留给空集，0留给$)
    string represent;   // 字符内容表示
    
public:
    Symbol(int symbol_type, int symbol_id, string symbol_content=""){
        type = symbol_type;
        sid = symbol_id;
        represent = symbol_content;
    }
    // 默认构造非法字符
    Symbol(){
        type = INVALID;
        sid = -1;
        represent = "";
    }
    int getType() const {return type;}
    int getID() const {return sid;}
    string getContent() const { return represent;}
    
    void setType(int symbol_type){
        type = symbol_type;
    }
    void setID(int symbol_id){
        sid = symbol_id;
    }
    void setContent(string content){
        represent = content;
    }
    // 对于Symbol会存在查找，排序等操作，因此需要操作符重载
    bool operator==(const Symbol &s) const {
        if(type == s.getType() && sid == s.getID()) return true;
        return false;
    }
    bool operator!=(const Symbol &s) const {
        if(type != s.getType() || sid != s.getID()) return true;
        return false;
    }
    bool operator<(const Symbol &s) const {
        if(type == s.type) return sid < s.sid;
        return type < s.type;
    }
    friend ostream& operator<<(ostream& os, const Symbol& sym){
        os<<sym.getContent();
        return os;
    }
};


#endif 