#pragma once
#ifndef AST_HPP
#define AST_HPP
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Symbols.hpp"
#include "globals.cpp"
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
    private:
        static ofstream file_decom;

    public:
        ASTNodeType type;
        Symbol *symbol;
        vector<AST*> children;
        AST(ASTNodeType type, Symbol *symbol);
        AST(ASTNodeType type, vector<AST*> children);
        AST(ASTNodeType type);
        ~AST();
        static string ast_decompiler (AST *ast);
    //     static void init_file() {
    //     file_decom.open("decompiler.txt");
    //     if (!file_decom.is_open()) {
    //         cout<< "Error opening file" << endl;
    //     }
    // }
    // static void close_file() {
    //     if (file_decom.is_open()) {
    //         file_decom.close();
    //     }
    // }
        
};
#endif