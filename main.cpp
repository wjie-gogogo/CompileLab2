#include <iostream>
#include "AnalyzeHelper.h"
#include "factory.h"
#include "SyntacticTreeNode.h"
#include "LR1Table.h"
#include <algorithm>
#include <fstream>


using namespace std;

// for syntacticTree
map<int,vector<string>> reduceMap;
vector<string> reduceVec;
int reduceNO = 0;

FILE* fIn;
FILE* fOut;

void printReduceMap(){
        for(auto item: reduceMap){
        cout<<item.first<<":";
        for(auto s: item.second){
            cout<< s<<" ";
        }
        cout<<endl;
    }
}

vector<Node> createTree(){
    vector<Node> Tree;
    int id = 1;
    // P的父亲节点的id为0
    Node P = Node(id++,"P",0,0);
    Tree.push_back(P);
    //逆序遍历
    for(map<int,vector<string>>::reverse_iterator rit = reduceMap.rbegin();rit!=reduceMap.rend();rit++){
        // cout<<(*rit).first<<endl;
        int fid;
        Node currFather;
        for(auto& node: Tree){
            if((node.data ==(*rit).second[0]) && (node.isfather ==0)){
                node.setIsFather();
                currFather = node;
                break;
            }
        }
        for(int i =0;i<(*rit).second.size();i++){

            string data = (*rit).second[i];
            if(i ==0){
                fid = currFather.id;
                continue;
            }
            Node son = Node(id++,data,fid,0);
            Tree.push_back(son);
        }      
    }
    return Tree;
}

// void processLexRes(){}

void mainFun(){

    // 产生式的工厂类 用于生成（非）终结符集 
    factory fac = factory();
    // 非终结符
    set<Symbol> Vn = fac.produceVNSymbol();
    // 终结符
    set<Symbol> Vt = fac.produceVtSymbol();
    // 产生式
    SetOfItems productions = fac.produceProduction();


    // cout<<productions<<endl;
    
    // 语法分析，建立项目集族
    AnalyzeHelper SA = AnalyzeHelper(Vt, Vn, productions);
    SetOfItems initialSet = SetOfItems();
    Symbol dollar(TERMINAL, 0, "$");
    Symbol S = Symbol(NONTERMINAL, 0, "S");
    Symbol program = Symbol(NONTERMINAL, 1, "P");
    Item it0 = Item(S, {program}, dollar);
    initialSet.appendItem(it0);

    cout<<"start create ClusterOfSets"<<endl;
    
    ClusterOfSets cos = SA.calcCluster(initialSet);
    // cout<<cos<<endl;
    // cout<<"6"<<endl;
    // 读入词法分析结果
    cout<<"please input the file name:"<<endl;
    string filename;

    while(getline(cin,filename)){
        fOut = fopen("D:\\processReduce.txt", "w");
        fIn = fopen(filename.c_str(),"r");
        if(fIn == NULL){
            cout<<"failed to open the file!"<<endl;
            continue;
        }
        vector<string> sentence;
        vector<Symbol> input;
        // 为了报错 语法出错的位置
        vector<int> errorRow;
        char ch;
        while ((ch = getc(fIn)) != EOF) {
            // cout<<ch<<endl;
            while (ch != '\n'&&ch != '\r') {
                // 处理空白
                while(ch == ' ' || ch == '\t'){
                    ch = getc(fIn);
                }
                string s;
                while(ch != ' ' && ch != '\n' && ch != '\t' && ch != '\r'){
                    s += ch;
                    ch = getc(fIn);
                }
                if(s.length())
                    sentence.push_back(s);
            }
            if(sentence.size() > 1){
                Symbol temp = Symbol(TERMINAL, stoi(sentence[1]), sentence[0]);
                input.push_back(temp);
                errorRow.push_back(stoi(sentence[3]));
                // 清空
                sentence.clear();
            }
        }
        input.push_back(dollar);

        
        //生成LR1分析表
        // cout<<"8"<<endl;
        LR1Table lr1tb;
        lr1tb.calcLR1Table(cos, productions);
        
        lr1tb.LR1Analyze(input, productions,errorRow);
        vector<Item> reduceProductions = lr1tb.getReduceProductions();
        for(auto it:reduceProductions){

            // 左边的规约式
            string left = it.getLeftSide().getContent();

            reduceVec.push_back(left);
            // 右边的
            string right = "";
            for(int i=0;i<it.getRightSide().size();i++){

                if(i != 0) right += " ";
                right += it.getRightSide()[i].getContent();
                reduceVec.push_back(it.getRightSide()[i].getContent());
            }
            reduceMap[reduceNO++] = reduceVec;

            reduceVec.clear();


            fprintf(fOut, "%s %s\n", left.c_str(), right.c_str());
        }

        fclose(fOut);
        // printReduceMap();
        vector<Node> Tree=createTree();

        for(auto n: Tree){
            cout<< "id: "<<n.id << " sym: " <<n.data<<" father id: "<<n.father<<" isfather: "<<n.isfather<<endl;
            // Tree.pop_back();
        }
        // Tree = new vector<Node>();
        // Tree.clear();

        // 完成一个词法分析文件结果 开始下一个
        cout<<"please input the file name:"<<endl;

    }

}



int main() {

    fOut = fopen("D:\\processReduce.txt", "w");

    mainFun();
    
    fclose(fIn);
    fclose(fOut);


    system("pause");
    return 0;
}

