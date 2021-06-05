#ifndef ClusterOfItems_h
#define ClusterOfItems_h
#include "SetOfItems.h"
#include <map>
/*
 * 项目集簇（所有的项目集）
 */
class ClusterOfSets{
private:
    vector<SetOfItems> vsets;
    int cnt;
    // 项目集ID:<项目集ID, 符号>
    // 例如 go[0,C] = 1
    vector<pair<int, Symbol>> gotoTable[300];
    // <项目集ID, 符号ID> -> isVisit ?
    // 默认值为false
    map<pair<int, Symbol>, bool> visitGoto;
  
public:
    ClusterOfSets(){
        cnt = 0;
    }
    // 添加项目集
    void appendItemSet(SetOfItems& soi){
        soi.setID(cnt++);
        vsets.push_back(soi);
    }
    vector<SetOfItems> getAllSets() const {
        return vsets;
    }
    int size() const {
        return cnt;
    }
    // 判断一个项目集是否在项目集族中
    bool existSet(SetOfItems itemSet) const {
        for(auto s : vsets){
            if(s == itemSet) return true;
        }
        return false;
    }
    // 查找set，返回其ID(下标）
    int searchSet(SetOfItems itemSet) const {
        for(auto s : vsets){
            if(s == itemSet) return s.getID();
        }
        return -1;
    }
    void updateGoto(int i, Symbol X, int j) {
        gotoTable[i].push_back(make_pair(j, X));
        visitGoto[make_pair(i, X)] = true;
    }
    bool isVisitGoto(int i, Symbol X){
        return visitGoto[make_pair(i, X)];
    }
    int getGoto(int i,  Symbol X) const{
        // return gotoTable[i][j]
        vector<pair<int, Symbol>> v = gotoTable[i];
        for(auto p:v){
            if(p.second == X)
                return p.first;
        }
        return -1;
    }
    
    friend ostream& operator<<(ostream& os, const ClusterOfSets& cos){
        os << "the cluster size is " << cos.size() << endl;
        for(auto s : cos.getAllSets()){
            os << s << endl;
        }
        return os;
    }
};
#endif /* SynHelper_h */