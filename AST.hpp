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
                    return (ast_decompiler(ast->children[0]) + " + " + ast_decompiler(ast->children[1]));
                    break;
                case SUB:
                    return ( ast_decompiler(ast->children[0]) + " - " + ast_decompiler(ast->children[1]));
                    break;

                case DIV:
                    return  ( ast_decompiler(ast->children[0]) + " / " + ast_decompiler(ast->children[1]));
                    break;
                case MULT:
                    return ( ast_decompiler(ast->children[0]) + " * " + ast_decompiler(ast->children[1]));
                    break;
                case SYMBOL:
                    return  ast->symbol->get_text();
                    break;
                case BIGGER:
                    return  ast_decompiler(ast->children[0]) + ">" + ast_decompiler(ast->children[1]);
                    break;
                case SMALLER:
                    return  ast_decompiler(ast->children[0]) + " < " + ast_decompiler(ast->children[1]);
                    break;
                case EQUAL:
                    return  ast_decompiler(ast->children[0]) + " = " + ast_decompiler(ast->children[1]);
                    break;
                case AND:
                    return  ast_decompiler(ast->children[0]) + " & " + ast_decompiler(ast->children[1]);
                    break;
                case OR:
                    return  ast_decompiler(ast->children[0]) + " | " + ast_decompiler(ast->children[1]);
                    break;
                case NOT:
                    return  '~' + ast_decompiler(ast->children[0]);
                    break;
                case ASSIGN:
                    return  ast_decompiler(ast->children[0]) + " = " + ast_decompiler(ast->children[1]);
                    break;
                case ASSIGN_VECTOR:
                    return  ast_decompiler(ast->children[0]) + "[" +  ast_decompiler(ast->children[1]) + "]" + " = " + ast_decompiler(ast->children[2]);
                    break;
                case RETURN:
                    return  "return" + ast_decompiler(ast->children[0]) + ";" + "\n";
                    break;
                case READ:
                    return ("read " + ast_decompiler(ast->children[0]) + ";" + "\n");
                    break;
                case WHILE:
                    return  "while(" + ast_decompiler(ast->children[0]) + ")" + "\n" + ast_decompiler(ast->children[1]) + "\n";
                    break;
                case IF:
                    return "if(" + ast_decompiler(ast->children[0]) + ")" + "then " + ast_decompiler(ast->children[1])   + "\n";
                    break;
                case IF_ELSE:
                    return "if(" + ast_decompiler(ast->children[0]) + ")" + "then " + ast_decompiler(ast->children[1]) + "\n" + "else " + ast_decompiler(ast->children[2]) + "\n";
                    break;
                case VECTOR:    
                    return ast_decompiler(ast->children[0]) + "[" + ast_decompiler(ast->children[1]) + "]";
                    break;
                case INT:
                    return "int";
                    break;
                case CHAR:
                    return "char";
                    break;
                case BLOCK:{
                    string block = "{ \n";
                     for( auto cmd : ast->children){
                           block += ast_decompiler(cmd)  + "\n";
                     }
                     block += "}" + "\n";
                    return block;
                    }
                    break;

               case FUNCALL:
                    return ast_decompiler(ast->children[0]) +"(" + ast_decompiler(ast->children[1]) + ")";
                    break;

               case DEC_VECTOR:
                    return  (ast_decompiler(ast->children[0]) + "[" + ast_decompiler(ast->children[1]) + "];" + "\n");
                    break;

               case DEC_VECTOR_INIT:
                   string dec_vector_init = ast_decompiler(ast->children[0]) + "[" + ast_decompiler(ast->children[1]) + "]" + "=" ;

                   for(int i = 2; i < ast->children.size(); i++){
                           dec_vector_init += ast_decompiler(ast->children[i]);
                    }

                    return dec_vector_init + ";" + "\n";
                    break;
               case DEC_VAR:

                    return ast_decompiler(ast->children[0]) + " " + ast_decompiler(ast->children[1]) + " = " + ast_decompiler(ast->children[2]) + ";" + "\n";
                   break;

               case PROGRAM:{

                    cout << ast->children.size() + "\n";
                    string program = ""; 

                    for (auto cmd : ast->children){
                        program = program + ast_decompiler(cmd) + "\n";
                    }
                   cout << program << endl;
                   return program;
               }

               case FUNC:{
                    string func = ast_decompiler(ast->children[0]) + " " + ast_decompiler(ast->children[1]) +  "(" + ast_decompiler(ast->children[2]) + ")";
                    return func + ast_decompiler(ast->children[3]);
                }

               case VAR:
                    return ast_decompiler(ast->children[0]) + " " + ast_decompiler(ast->children[1]);

               case INIT:{

                    string init;
                    for (auto init : ast->children){
                        init += ast_decompiler(init) + "," + "\n";
                    }
                    return init;
               }

               case PARAM:{

                    string param_s;
                    for (auto param : ast->children){
                        param_s += ast_decompiler(param) + ", ";
                    }

                    return param_s;
               }

                case ARG_LIST:{
                string args
                    for (auto arg : ast->children){
                        args += ast_decompiler(arg) + ", ";
                    }
                    return args;
                }
            } 
            return "";          
        }
        /**
        static void print_ast (AST *ast, int level = 0) {
            if (ast == NULL) return;
            for (int i = 0; i < level; i++) cout + "  " + level;
            switch (ast->type) {
                case ADD:
                    cout + "ADD" + "\n";
                    break;
                case SUB:
                    cout + "SUB" + "\n";
                    break;
                case DIV:
                    cout + "DIV" + "\n";
                    break;
                case MULT:
                    cout + "MULT" + "\n";
                    break;
                case SYMBOL:
                    cout + "SYMBOL: " + ast->symbol->get_type() + ast->symbol->get_text() + "\n";
                    break;
                case BIGGER:
                    cout + "BIGGER" + "\n";
                    break;
                case SMALLER:
                    cout + "SMALLER" + "\n";
                    break;
                case EQUAL:
                    cout + "EQUAL" + "\n";
                    break;
                case AND:
                    cout + "AND" + "\n";
                    break;
                case OR:
                    cout + "OR" + "\n";
                    break;
                case NOT:
                    cout + "NOT" + "\n";
                    break;
                case ASSIGN:
                    cout + "ASSIGN" + "\n";
                    break;
                case ASSIGN_VECTOR:
                    cout + "ASSIGN_VECTOR" + "\n";
                    break;
                case RETURN:
                    cout + "RETURN" + "\n";
                    break;
                case READ:
                    cout + "READ" + "\n";
                    break;
                case WHILE:
                    cout + "WHILE" + "\n";
                    break;
                case IF:
                    cout + "IF" + "\n";
                    break;
                case IF_ELSE:
                    cout + "IF_ELSE" + "\n";
                    break;
                case VECTOR:    
                    cout + "VECTOR" + "\n";
                    break;
                case INT:
                    cout + "INT" + "\n";
                    break;
                case CHAR:
                    cout + "CHAR" + "\n";
                    break;
                case BLOCK:
                    cout + "BLOCK" + "\n";
                    break;
                case FUNCALL:
                    cout + "FUNCALL" + "\n";
                    break;
                case DEC_VECTOR:
                    cout + "DEC_VECTOR" + "\n";
                    break;
                case DEC_VECTOR_INIT:
                    cout + "DEC_VECTOR_INIT" + "\n";
                    break;
                case DEC_VAR:  
                    cout + "DEC_VAR" + "\n";
                    break;
                case PROGRAM:
                    cout + "PROGRAM" + "\n";
                    break;
                case FUNC:
                    cout + "FUNC" + "\n";
                    break;
                case VAR:
                    cout + "VAR" + "\n";
                    break;
                case INIT:
                    cout + "INIT" + "\n";
                    break;
                case PARAM:
                    cout + "PARAM" + "\n";
                    break;
                case ARG_LIST:
                    cout + "ARG_LIST" + "\n";
                    break;
            }
            for (AST* child : ast->children) {
                print_ast(child, level + 1);
            }
        
       } **/
};
#endif