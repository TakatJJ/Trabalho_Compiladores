#pragma once
#include <vector>
#include <iostream>
#include "Symbols.hpp"
#include "AST.cpp"
#include <string>
using namespace std;
class AST {
    public:
        ASTNodeType type;
        Symbol *symbol;
        vector<AST*> children;
        AST(ASTNodeType type, Symbol *symbol) : type(type), symbol(symbol), children(vector<AST*>()) {}
        AST(ASTNodeType type, Symbol *symbol, vector<AST*> children) : type(type), symbol(symbol), children(children) {}
        ~AST() {
        for (AST* child : children) {
            delete child;
        }
        }
};
