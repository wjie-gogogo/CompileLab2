

#ifndef LR1Table_h
#define LR1Table_h

#include "AnalyzeHelper.h"
#include <stack>
/* action表中的表项*/
class ActionItem{
private:
    int type;   // 1表示S(移进）, 2表示R（规约），3表示ACC
    int state;  // 若是S，则对应下一个项目集的ID；若是R和ACC则表示，用来规约的产生式的ID
    
public:
    ActionItem(int type, int state){
        this->type = type;
        this->state = state;
    }
    ActionItem(){
        
    }
    int getType() const {
        return type;
    }
    int getState() const {
        return state;
    }
    void setType(int newType){
        type = newType;
    }
    void setState(int newState){
        state = newState;
    }
};


/* LR1表，包括action和goto */
class LR1Table{
private:
    // Action[项目集ID][符号ID] = Sj | Rj
    ActionItem Action[300][300];
    // Goto[项目集ID][符号ID] = 项目集ID
    int Goto[300][300];
    // 所有的使用到的reduce的产生式
    vector<Item> reduceProductions;
    
public:
    LR1Table(){

    }
    vector<Item> getReduceProductions() const {
        return reduceProductions;
    }
    // 对于项目集规范族C中的每个项目集（状态），分析动作如下：
    // 若[A -> alpha . a beta, b]在其中，且go[
    void calcLR1Table(ClusterOfSets C, SetOfItems productions){
        for(auto itemSet : C.getAllSets()){
            for(auto it : itemSet.getVitems()){
                Symbol ahead = it.getAhead();
                Symbol nextSym = it.symbolAfterDot();
                if(it.isReductionItem()){
                    // 若[A -> alpha . , $]，且A=S',则置action[i,$] = ACC
                    if(it.getLeftSide() == productions.getVitems()[0].getLeftSide()){
                        Action[itemSet.getID()][ahead.getID()] = ActionItem(3, 0);
                    }
                    // 若[A -> alpha ., a]，且A!=S',则置action[i,a] = Rj
                    else{
                       Action[itemSet.getID()][ahead.getID()] = ActionItem(2, productions.getProductionID(it));
                    }
                }
                else{
                    // 若[A -> alpha . a beta, b]，且go(Ii, a) = Ij.则置action[i,a] = Sj
                    if(nextSym.getType() == TERMINAL){
                        int nextState = C.getGoto(itemSet.getID(), nextSym);
                        Action[itemSet.getID()][nextSym.getID()] = ActionItem(1, nextState);
                    }
                    // 对于非终结符A,有go(Ii, A) = Ij,则置goto[i,A] = j
                    else if(nextSym.getType() == NONTERMINAL){
                        int nextState = C.getGoto(itemSet.getID(), nextSym);
                        Goto[itemSet.getID()][nextSym.getID()] = nextState;
                    }
                }
            }
        }
    }


    // 打印符号栈信息
    void printStackInfo(vector<Symbol> symbolStack, vector<int> stateStack){
        // assert(symbolStack.size() == stateStack.size());
        cout<<endl;
        // 打印状态栈
        printf("State :");
        for(int i=0;i<stateStack.size();i++){
            printf("%-5d", stateStack[i]);
        }
        printf("\n");
        // 打印符号栈
        printf("Symbol:");
        for(int i=0;i<symbolStack.size();i++){
            printf("%-5s", symbolStack[i].getContent().c_str());
        }
        cout<<endl<<endl;
    }
    
    // 根据LR1表进行分析
    void LR1Analyze(vector<Symbol> inputStr, SetOfItems productions,vector<int> errorRow){
        // 这里使用vector而不是stack，是因为方便打印信息
        vector<Symbol> symbolStack;
        vector<int> stateStack;
        // initalize
        stateStack.push_back(0);
        symbolStack.push_back(Symbol(TERMINAL, -1, "-"));
        int pos = 0;
        Symbol s = inputStr[pos];
        int row = errorRow[pos];
        
        while(pos < inputStr.size()){
            ActionItem nowAction = Action[stateStack.back()][s.getID()];

            Item prod;

            switch (nowAction.getType()) {
                case 1:     // shift in
                    symbolStack.push_back(s);
                    stateStack.push_back(nowAction.getState());
                    s = inputStr[++pos];
                    row = errorRow[pos];
                    break;
                case 2:     // reduce
                    prod = productions.getVitems()[nowAction.getState()];
                    // 产生式右边为空，不用弹出
                    if(prod.getRightSide()[0].getID() != -1){
                        for(int i=0;i<prod.getRightSide().size();i++){
                            symbolStack.pop_back();
                            stateStack.pop_back();
                        }
                    }
                    reduceProductions.push_back(prod);
                    symbolStack.push_back(prod.getLeftSide());
                    stateStack.push_back(Goto[stateStack.back()][prod.getLeftSide().getID()]);
                    break;
                case 3:     // ACC

                    cout<<"ACCEPT!"<<endl;
                    return;
                    break;
                default:
                    printf("An error occurs! And it near line:%d \n ",row);
                    // printf("An error occurs! And it happened at line:%d \n ",row);
                    prod = productions.getVitems()[nowAction.getState()];
                    cout<<prod<<endl;
                    return;
                    break;
            }
            // 每次循环打印栈信息
            printStackInfo(symbolStack, stateStack);
        }
    }

    void printGotoTable(int stateNum, int nonterminalNum){
        for(int i=0;i<stateNum;i++){
            for(int j=0;j<nonterminalNum;j++){
                printf("%3d", Goto[i][j]);
            }
            printf("\n");
        }
    }
};

#endif
