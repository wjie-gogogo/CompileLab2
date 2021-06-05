#ifndef Factory_h
#define Factory_h
#include "AnalyzeHelper.h"


#define TERMINAL 0
#define NONTERMINAL 1
#define INVALID -1
// 根据文法 生成对应的符号 产生式等
class factory{

private:
    Symbol dollar = Symbol(TERMINAL,0,"$");

    Symbol INT = Symbol(TERMINAL, 1, "int");
    Symbol BOOL = Symbol(TERMINAL, 2, "bool");
    Symbol CHAR= Symbol(TERMINAL, 3 , "char");

    Symbol IF = Symbol(TERMINAL, 4, "if");
    Symbol ELSE = Symbol(TERMINAL, 5, "else");
    Symbol WHILE = Symbol(TERMINAL, 6, "while");
    Symbol GET = Symbol(TERMINAL, 7, "get");
    Symbol PUT = Symbol(TERMINAL, 8 , "put");
    Symbol MAIN = Symbol(TERMINAL, 9, "main");
    Symbol RETURN = Symbol(TERMINAL, 10, "return");

    Symbol add = Symbol(TERMINAL, 114, "+");
    Symbol sub = Symbol(TERMINAL, 115, "-");
    Symbol mul = Symbol(TERMINAL, 116, "*");
    Symbol div = Symbol(TERMINAL, 117, "/");
    Symbol equal = Symbol(TERMINAL, 108, "=");
    Symbol dEqual = Symbol(TERMINAL, 109, "==");
    Symbol less = Symbol(TERMINAL, 101, "<");
    Symbol lessEqual = Symbol(TERMINAL, 102, "<=");
    Symbol notEqual = Symbol(TERMINAL, 106, "!=");
    Symbol greater = Symbol(TERMINAL, 104, ">");
    Symbol gEqual = Symbol(TERMINAL, 105, ">=");
    Symbol dAND = Symbol(TERMINAL, 113, "&&");
    Symbol dOR = Symbol(TERMINAL, 112, "||");
    Symbol NOT = Symbol(TERMINAL, 107, "!");
    Symbol SLParenthese = Symbol(TERMINAL, 118, "(");
    Symbol SRParenthese = Symbol(TERMINAL, 119, ")");
    Symbol BLParenthese = Symbol(TERMINAL, 120, "{");
    Symbol BRParenthese = Symbol(TERMINAL, 121, "}");
    Symbol MLParenthese = Symbol(TERMINAL, 125, "[");
    Symbol MRParenthese = Symbol(TERMINAL, 126, "]");
    Symbol comma = Symbol(TERMINAL, 122, ",");
    Symbol semicolon = Symbol(TERMINAL, 123, ";");
    Symbol sAND = Symbol(TERMINAL, 111, "&");
    Symbol sOR = Symbol(TERMINAL, 110, "|");
    Symbol id = Symbol(TERMINAL, 200, "id");
    Symbol num = Symbol(TERMINAL, 127, "num");
    Symbol null = Symbol(TERMINAL, -1, "null");

    Symbol S = Symbol(NONTERMINAL, 0, "S");
    Symbol program = Symbol(NONTERMINAL, 1, "P");
    Symbol external_declarations = Symbol(NONTERMINAL, 2, "EDS");
    Symbol function_declarations = Symbol(NONTERMINAL, 3, "FDS");
    Symbol var_declarations = Symbol(NONTERMINAL, 4, "VDS");
    Symbol var_declaration = Symbol(NONTERMINAL, 5, "VD");
    Symbol type = Symbol(NONTERMINAL, 6, "TYPE");
    Symbol expression_list = Symbol(NONTERMINAL, 7, "EL");
    Symbol expression = Symbol(NONTERMINAL, 8, "E");
    Symbol simple_expression = Symbol(NONTERMINAL, 9, "SE");
    Symbol term = Symbol(NONTERMINAL, 10, "T");
    Symbol factor = Symbol(NONTERMINAL, 11, "F");
    Symbol formal_parameter = Symbol(NONTERMINAL, 12, "FP");
    Symbol parameter_list = Symbol(NONTERMINAL, 13, "PL");
    Symbol parameter_declaration = Symbol(NONTERMINAL, 14, "PD");
    Symbol compound_statement = Symbol(NONTERMINAL, 15, "CS");
    Symbol statement_list = Symbol(NONTERMINAL, 16, "SL");
    Symbol statement = Symbol(NONTERMINAL, 17, "ST");
    Symbol call_func_statement = Symbol(NONTERMINAL, 18, "CFS");
    Symbol func_name = Symbol(NONTERMINAL, 19, "FN");
    Symbol func_keyword = Symbol(NONTERMINAL, 20, "FK");
    Symbol else_part = Symbol(NONTERMINAL, 21, "EP");
    Symbol constant = Symbol(NONTERMINAL, 22, "C");
    Symbol relop = Symbol(NONTERMINAL, 23, "relop");
    Symbol addop = Symbol(NONTERMINAL, 24, "addop");
    Symbol mulop = Symbol(NONTERMINAL, 25, "mulop");

public:
    // 生成Vn符号集
    set<Symbol> produceVNSymbol(){    
        set<Symbol> Vn;
        Vn.insert(S);
        Vn.insert(program);
        Vn.insert(external_declarations);
        Vn.insert(function_declarations);
        Vn.insert(var_declarations);
        Vn.insert(var_declaration);
        Vn.insert(type);
        Vn.insert(expression_list);
        Vn.insert(expression);
        Vn.insert(simple_expression);
        Vn.insert(term);
        Vn.insert(factor);
        Vn.insert(formal_parameter);
        Vn.insert(parameter_list);
        Vn.insert(parameter_declaration);
        Vn.insert(compound_statement);
        Vn.insert(statement_list);
        Vn.insert(statement);
        Vn.insert(call_func_statement);
        Vn.insert(func_name);
        Vn.insert(func_keyword);
        Vn.insert(else_part);
        Vn.insert(constant);
        Vn.insert(relop);
        Vn.insert(addop);
        Vn.insert(mulop);
        return Vn;
    }
    // 生成Vt符号集
    set<Symbol> produceVtSymbol(){
        set<Symbol> Vt;
        Vt.insert(dollar);
        Vt.insert(MAIN);
        Vt.insert(IF);
        Vt.insert(ELSE);
        Vt.insert(WHILE);
        Vt.insert(GET);
        Vt.insert(PUT);
        Vt.insert(RETURN);
        Vt.insert(INT);
        Vt.insert(BOOL);
        Vt.insert(CHAR);
        Vt.insert(add);
        Vt.insert(sub);
        Vt.insert(mul);
        Vt.insert(div);
        Vt.insert(equal);
        Vt.insert(dEqual);
        Vt.insert(less);
        Vt.insert(lessEqual);
        Vt.insert(greater);
        Vt.insert(gEqual);
        Vt.insert(dAND);
        Vt.insert(dOR);
        Vt.insert(NOT);
        Vt.insert(SLParenthese);
        Vt.insert(SRParenthese);
        Vt.insert(BLParenthese);
        Vt.insert(BRParenthese);
        Vt.insert(MLParenthese);
        Vt.insert(MRParenthese);
        Vt.insert(comma);
        Vt.insert(semicolon);
        Vt.insert(sAND);
        Vt.insert(sOR);
        Vt.insert(id);
        Vt.insert(num);
        Vt.insert(null);
        return Vt;
    }

    SetOfItems produceProduction(){
        SetOfItems productions = SetOfItems();
        
        Item it1 = Item(S, {program}, Symbol());   
        productions.appendItem(Item(S,{program},Symbol()));
        productions.appendItem(Item(program, {external_declarations}, Symbol()));     
        productions.appendItem(Item(program, {program, external_declarations}, Symbol()));

        productions.appendItem(Item(external_declarations, {function_declarations}, Symbol()));

        productions.appendItem(Item(external_declarations, {var_declarations}, Symbol()));

        productions.appendItem(Item(var_declarations, {type, var_declaration, semicolon}, Symbol()));
        productions.appendItem(Item(var_declaration, {id}, Symbol()));
        productions.appendItem(Item(var_declaration, {id, equal, expression}, Symbol()));
        productions.appendItem(Item(var_declaration, {var_declaration, comma, id}, Symbol()));
        productions.appendItem(Item(var_declaration, {var_declaration, comma, id, equal, expression}, Symbol()));
        productions.appendItem(Item(type, {INT}, Symbol()));
        productions.appendItem(Item(type, {BOOL}, Symbol()));
        productions.appendItem(Item(type, {CHAR}, Symbol()));
        productions.appendItem(Item(function_declarations, {type, id, formal_parameter, compound_statement}, Symbol()));
        productions.appendItem(Item(formal_parameter, {SLParenthese,parameter_list, SRParenthese}, Symbol()));
        productions.appendItem(Item(formal_parameter, {SLParenthese, SRParenthese}, Symbol()));
        productions.appendItem(Item(parameter_list, {parameter_declaration}, Symbol()));
        productions.appendItem(Item(parameter_list, {parameter_list, comma, parameter_declaration}, Symbol()));
        productions.appendItem(Item(parameter_declaration, {type, id}, Symbol()));
        productions.appendItem(Item(parameter_declaration, {type, id, equal, constant}, Symbol()));
        productions.appendItem(Item(compound_statement, {BLParenthese, statement_list, BRParenthese}, Symbol()));
        productions.appendItem(Item(statement_list, {statement}, Symbol()));
        productions.appendItem(Item(statement_list, {statement_list, statement}, Symbol()));
        productions.appendItem(Item(statement, {var_declarations}, Symbol()));
        productions.appendItem(Item(statement, {id, equal, expression, semicolon}, Symbol()));
        productions.appendItem(Item(statement, {semicolon}, Symbol()));
        productions.appendItem(Item(statement, {compound_statement}, Symbol()));
        productions.appendItem(Item(statement, {call_func_statement}, Symbol()));
        productions.appendItem(Item(statement, {IF, SLParenthese, expression, SRParenthese, compound_statement, else_part}, Symbol()));
        productions.appendItem(Item(statement, {WHILE, SLParenthese, expression, SRParenthese, compound_statement}, Symbol()));
        productions.appendItem(Item(else_part, {ELSE, BLParenthese, statement, BRParenthese}, Symbol()));
        productions.appendItem(Item(else_part, {null}, Symbol()));
        productions.appendItem(Item(call_func_statement, {func_name, SLParenthese, expression_list, SRParenthese, semicolon}, Symbol()));
        productions.appendItem( Item(func_name, {id}, Symbol()));
        productions.appendItem(Item(func_name, {func_keyword}, Symbol()));
        productions.appendItem(Item(expression_list, {expression_list, comma, expression}, Symbol()));
        productions.appendItem(Item(expression_list, {expression}, Symbol()));
        productions.appendItem(Item(expression, {simple_expression, relop, simple_expression}, Symbol()));
        productions.appendItem(Item(expression, {simple_expression}, Symbol()));
        productions.appendItem(Item(simple_expression, {simple_expression, addop, term}, Symbol()));
        productions.appendItem( Item(simple_expression, {term}, Symbol()));
        productions.appendItem(Item(term, {term, mulop, factor}, Symbol()));
        productions.appendItem(Item(term, {factor}, Symbol()));
        productions.appendItem(Item(factor, {SLParenthese, expression, SRParenthese}, Symbol()));
        productions.appendItem(Item(factor, {id}, Symbol()));
        productions.appendItem(Item(factor, {constant}, Symbol()));
        productions.appendItem(Item(factor, {NOT, factor}, Symbol()));
        productions.appendItem(Item(constant, {num}, Symbol()));
        productions.appendItem(Item(function_declarations, {INT, MAIN, SLParenthese, SRParenthese, compound_statement}, Symbol()));
        productions.appendItem(Item(relop, {dEqual}, Symbol()));
        productions.appendItem(Item(relop, {notEqual}, Symbol()));
        productions.appendItem(Item(relop, {less}, Symbol()));
        productions.appendItem(Item(relop, {lessEqual}, Symbol()));
        productions.appendItem(Item(relop, {greater}, Symbol()));
        productions.appendItem(Item(relop, {gEqual}, Symbol()));
        productions.appendItem(Item(addop, {add}, Symbol()));
        productions.appendItem(Item(addop, {sub}, Symbol()));
        productions.appendItem(Item(addop, {dOR}, Symbol()));
        productions.appendItem(Item(addop, {sOR}, Symbol()));
        productions.appendItem(Item(mulop, {mul}, Symbol()));
        productions.appendItem(Item(mulop, {div}, Symbol()));
        productions.appendItem(Item(mulop, {dAND}, Symbol()));
        productions.appendItem(Item(mulop, {sAND}, Symbol()));
        productions.appendItem(Item(compound_statement, {BLParenthese, BRParenthese}, Symbol()));
        productions.appendItem(Item(func_keyword, {GET}, Symbol()));
        productions.appendItem(Item(func_keyword, {PUT}, Symbol()));
        return productions;
    }
};
#endif