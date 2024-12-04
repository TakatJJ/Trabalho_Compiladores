#pragma once
#ifndef AST_HPP
#define AST_HPP
#include "Symbols.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum ASTNodeType {
  ADD,           // PRONTO
  SUB,           // PRONTO
  DIV,           // PRONTO
  MULT,          // PRONTO
  SYMBOL,        // PRONTO
  BIGGER,        // PRONTO
  SMALLER,       // PRONTO
  EQUAL,         // PRONTO
  AND,           // PRONTO
  OR,            // PRONTO
  NOT,           // PRONTO
  ASSIGN,        // PRONTO
  ASSIGN_VECTOR, // PRONTO
  RETURN,
  PRINT,   // PRONTO
  READ,    // PRONTO
  WHILE,   // PRONTO
  IF,      // PRONTO
  IF_ELSE, // PRONTO
  VECTOR,  // PRONTO
  INT,     // PRONTO
  CHAR,    // PRONTO
  BLOCK,   // PRONTO
  FUNCALL,
  DEC_VECTOR, // PRONT
  DEC_VECTOR_INIT,
  DEC_VAR, // PRONTO
  PROGRAM, // PRONTO
  DEC_FUNC,
  INIT, // PRONTO
  PARAM,
  PARAMLIST,
  ARG_LIST,
  EMPTY // PRONTO
};
class AST {
private:
  static ofstream file_decom;

public:
  ASTNodeType type;
  Symbol *symbol;
  vector<AST *> children;
  AST(ASTNodeType type, Symbol *symbol);
  AST(ASTNodeType type, vector<AST *> children);
  AST(ASTNodeType type);
  ~AST();
  static string ast_decompiler(AST *ast);
  static void print_ast(AST *ast, int level = 0);
  static string ast_type_to_string(AST *ast);
};
#endif
