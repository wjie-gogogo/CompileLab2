
#ifndef SyntacticTreeNode_h
#define SyntacticTreeNode_h

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node{
public:
    int id;
    string data;
    int father = -1;
    bool isfather = 0;

    Node(){}
    Node(int i,string data){
        this->id = i;
        this->data = data;
    }

    Node(int i,string data,int father,bool isfather=0){
        this->id = i;
        this ->data =data;
        this->father =father;
        this->isfather = isfather;
    }

    void setIsFather(){
        this->isfather =1;
    }


};




#endif