#ifndef AST_HPP
#define AST_HPP
#include <vector>
#include <iostream>
#include "Symbols.hpp"
#include <string>
using namespace std;

enum ASTNodeType {
    ADD,
    SUB,
    DIV,
    MULT,
    SYMBOL,
    BIGGER,
    SMALLER,
    EQUAL,
    AND,
    OR,
    NOT,
    ASSIGN,
    ASSIGN_VECTOR,
    RETURN,
    READ,
    WHILE,
    IF,
    IF_ELSE,
    VECTOR,
    INT,
    CHAR
    };
class AST {
    public:
        ASTNodeType type;
        Symbol *symbol;
        vector<AST*> children;
        AST(ASTNodeType type, Symbol *symbol) {
            this->type = type;
            this->symbol = symbol;
        }
        AST(ASTNodeType type, vector<AST*> children) {
            this->type = type;
            this->children = children;
        }
        AST(ASTNodeType type) {
            this->type = type;
        }
        ~AST() {
        for (AST* child : children) {
            delete child;
        }
        }
        static void print_ast (AST *ast, int level = 0) {
            if (ast == NULL) return;
            for (int i = 0; i < level; i++) cout << "  ";
            switch (ast->type) {
                case ADD:
                    cout << "ADD" << endl;
                    break;
                case SUB:
                    cout << "SUB" << endl;
                    break;
                case DIV:
                    cout << "DIV" << endl;
                    break;
                case MULT:
                    cout << "MULT" << endl;
                    break;
                case SYMBOL:
                    cout << "SYMBOL: " << ast->symbol->get_type() << endl;
                    break;
                case BIGGER:
                    cout << "BIGGER" << endl;
                    break;
                case SMALLER:
                    cout << "SMALLER" << endl;
                    break;
                case EQUAL:
                    cout << "EQUAL" << endl;
                    break;
                case AND:
                    cout << "AND" << endl;
                    break;
                case OR:
                    cout << "OR" << endl;
                    break;
                case NOT:
                    cout << "NOT" << endl;
                    break;
            }
            for (AST* child : ast->children) {
                print_ast(child, level + 1);
            }
        }
};
#endif