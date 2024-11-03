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
    PRINT,
    READ,
    WHILE,
    IF,
    IF_ELSE,
    VECTOR,
    INT,
    CHAR,
    BLOCK,
    FUNCALL,
    DEC_VECTOR,
    DEC_VECTOR_INIT,
    DEC_VAR,
    PROGRAM,
    FUNC,
    VAR,
    INIT,
    PARAM,
    ARG_LIST
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
        static string ast_decompiler (AST *ast) {

            if (ast == NULL) return "";

            switch (ast->type) {
                case ADD:
                    cout << ast_decompiler(ast->children[0]) << " + " << ast_decompiler(ast->children[1]);
                    break;
                case SUB:
                    cout << ast_decompiler(ast->children[0]) << " - " << ast_decompiler(ast->children[1]);
                    break;

                case DIV:
                    cout << ast_decompiler(ast->children[0]) << " / " << ast_decompiler(ast->children[1]);
                    break;
                case MULT:
                    cout << ast_decompiler(ast->children[0]) << " * " << ast_decompiler(ast->children[1]);
                    break;
                case SYMBOL:
                    return  ast->symbol->get_text();
                    break;
                case BIGGER:
                    cout << ast_decompiler(ast->children[0]) << " > " << ast_decompiler(ast->children[1]);
                    break;
                case SMALLER:
                    cout << ast_decompiler(ast->children[0]) << " < " << ast_decompiler(ast->children[1]);
                    break;
                case EQUAL:
                    cout << ast_decompiler(ast->children[0]) << " = " << ast_decompiler(ast->children[1]);
                    break;
                case AND:
                    cout << ast_decompiler(ast->children[0]) << " & " << ast_decompiler(ast->children[1]);
                    break;
                case OR:
                    cout << ast_decompiler(ast->children[0]) << " | " << ast_decompiler(ast->children[1]);
                    break;
                case NOT:
                    cout << '~' << ast_decompiler(ast->children[0]);
                    break;
                case ASSIGN:
                    cout << ast_decompiler(ast->children[0]) << " = " << ast_decompiler(ast->children[1]);
                    break;
                case ASSIGN_VECTOR:
                    cout << ast_decompiler(ast->children[0]) << "[" <<  ast_decompiler(ast->children[1]) << "]" << " = " << ast_decompiler(ast->children[2]);
                    break;
                case RETURN:
                    cout << "return" << ast_decompiler(ast->children[0]) << ";" << endl;
                    break;
                case READ:
                    cout << "read" << ast_decompiler(ast->children[0]) << ";" << endl;
                    break;
                case WHILE:
                    cout << "while(" << ast_decompiler(ast->children[0]) << ")" << endl << ast_decompiler(ast->children[1]) << endl;
                    break;
                case IF:
                    cout << "if(" << ast_decompiler(ast->children[0]) << ")" << "then " << ast_decompiler(ast->children[1])   << endl;
                    break;
                case IF_ELSE:
                    cout << "if(" << ast_decompiler(ast->children[0]) << ")" << "then " << ast_decompiler(ast->children[1]) << endl << "else " << ast_decompiler(ast->children[2]) << endl;
                    break;
                case VECTOR:    
                    cout << ast_decompiler(ast->children[0]) << "[" << ast_decompiler(ast->children[1]) << "]";
                    break;
                case INT:
                    return"int";
                    break;
                case CHAR:
                    return "char";
                    break;
                case BLOCK:
                     cout << "{";
                     for( auto cmd : ast->children){
                           cout << ast_decompiler(cmd) << endl;
                     }
                     cout << "}" << endl;

                    break;

               case FUNCALL:
                    cout << ast_decompiler(ast->children[0]) <<"(" << ast_decompiler(ast->children[1])<< ")";
                     break;

               case DEC_VECTOR:
                    cout << ast_decompiler(ast->children[0]) << "[" << ast_decompiler(ast->children[1]) << "];" << endl;
                    break;

               case DEC_VECTOR_INIT:
                   cout << ast_decompiler(ast->children[0]) << "[" << ast_decompiler(ast->children[1]) << "]" << "=" ;

                   for(int i = 2; i < ast->children.size(); i++){
                           cout << ast_decompiler(ast->children[i]);
                    }

                    cout << ";" << endl;
                    break;
               case DEC_VAR:
                    cout << ast_decompiler(ast->children[0]) << " " << ast_decompiler(ast->children[1]) << " = " << ast_decompiler(ast->children[2]) << ";" << endl;
                   break;

               case PROGRAM:

                    cout << ast->children.size() << endl;

                    string program = ""; 
                    for (auto cmd : ast->children){
                        cout << ast_decompiler(cmd) << endl;
                    }
                    cout << "EOF" << endl;
                    return "";
                   break;

               case FUNC:
                    cout << ast_decompiler(ast->children[0]) << " " << ast_decompiler(ast->children[1]) <<  "(" << ast_decompiler(ast->children[2]) << ")";
                    cout << ast_decompiler(ast->children[3]);
                   break;
               case VAR:
                    cout << ast_decompiler(ast->children[0]) << " " << ast_decompiler(ast->children[1]);
                   break;

               case INIT:
                    for (auto init : ast->children){
                        cout << ast_decompiler(init) << "," << endl;
                    }
                   break;

               case PARAM:
                    for (auto param : ast->children){
                        cout << ast_decompiler(param) << ", ";
                    }
                   break;
                case ARG_LIST:
                    for (auto arg : ast->children){
                        cout << ast_decompiler(arg) << ", ";
                    }
                   break;
            } 
            return "";          
        }
        
        static void print_ast (AST *ast, int level = 0) {
            if (ast == NULL) return;
            for (int i = 0; i < level; i++) cout << "  " << level;
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
                    cout << "SYMBOL: " << ast->symbol->get_type() << ast->symbol->get_text() << endl;
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
                case ASSIGN:
                    cout << "ASSIGN" << endl;
                    break;
                case ASSIGN_VECTOR:
                    cout << "ASSIGN_VECTOR" << endl;
                    break;
                case RETURN:
                    cout << "RETURN" << endl;
                    break;
                case READ:
                    cout << "READ" << endl;
                    break;
                case WHILE:
                    cout << "WHILE" << endl;
                    break;
                case IF:
                    cout << "IF" << endl;
                    break;
                case IF_ELSE:
                    cout << "IF_ELSE" << endl;
                    break;
                case VECTOR:    
                    cout << "VECTOR" << endl;
                    break;
                case INT:
                    cout << "INT" << endl;
                    break;
                case CHAR:
                    cout << "CHAR" << endl;
                    break;
                case BLOCK:
                    cout << "BLOCK" << endl;
                    break;
                case FUNCALL:
                    cout << "FUNCALL" << endl;
                    break;
                case DEC_VECTOR:
                    cout << "DEC_VECTOR" << endl;
                    break;
                case DEC_VECTOR_INIT:
                    cout << "DEC_VECTOR_INIT" << endl;
                    break;
                case DEC_VAR:  
                    cout << "DEC_VAR" << endl;
                    break;
                case PROGRAM:
                    cout << "PROGRAM" << endl;
                    break;
                case FUNC:
                    cout << "FUNC" << endl;
                    break;
                case VAR:
                    cout << "VAR" << endl;
                    break;
                case INIT:
                    cout << "INIT" << endl;
                    break;
                case PARAM:
                    cout << "PARAM" << endl;
                    break;
                case ARG_LIST:
                    cout << "ARG_LIST" << endl;
                    break;
            }
            for (AST* child : ast->children) {
                print_ast(child, level + 1);
            }
        
        }
};
#endif