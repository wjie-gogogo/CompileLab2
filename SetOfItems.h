#ifndef SetOfItems_h
#define SetOfItems_h
#include "Item.h"
/*
 * 项目集
 */
class SetOfItems{
private:
    vector<Item> vitems;
    int id;
    int cnt;

    
public:
    SetOfItems(){
        cnt = 0;
    }
    vector<Item> getVitems() const {
        return vitems;
    }
    int getProductionID(Item it){
        for(int i=0;i<cnt;i++){
            Item cur = vitems[i];
            if(cur.equal(it)){
                return i;
            }
        }
        return -1;
    }
    int size() const {
        return cnt;
    }
    void setID(int set_id){
        id = set_id;
    }
    int getID() const {
        return id;
    }
    void setVitems(vector<Item> vec_of_item){
        vitems = vec_of_item;
    }
    // 将一个项目添加到项目集
    void appendItem(Item it){
        it.setID(cnt++);
        vitems.push_back(it);
    }
    // 判断项目(Item)是否存在于项目集中
    bool existItem(Item it) const {
        for(auto vit: vitems){
            if(vit == it) return true;
        }
        return false;
    }
    bool operator==(const SetOfItems& soi) const {
        return vitems == soi.vitems;
        // if(vitems.size() != soi.getVitems().size()){
        //     return false;
        // }
        // for(auto curItem: vitems){
        //     if(!soi.existItem(curItem))
        //         return false;
        // }
        // return true;
    }
    friend ostream& operator<<(ostream& os, const SetOfItems& soi){
        os << "the set id is" << soi.getID() << endl;
        for(auto it : soi.getVitems()){
            os << it << endl;
        }
        return os;
    }
};

#endif