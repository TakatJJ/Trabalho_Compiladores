#pragma once
#include "Symbols.hpp"
#include "AST.hpp"
#include <map>

extern int semantic_errors;
extern map<string, Symbol> symbols_table;

void check_semantic(AST* node);
void check_and_set_declarations(AST* node);
void check_undeclared(AST* node);
bool DatatypeCompatible(int datatype1, int datatype2);
bool IntegerOrChar(int datatype);
bool checkVectorElements(AST* node, int datatype);
bool checkVectorSizeInit(AST* node);
int removeStartingSymbol(string s);
void handleCommands(AST* node);
pair<int,int> type_infer(AST *node);
bool valid_id(std::pair<int,int> expr, AST *p);
