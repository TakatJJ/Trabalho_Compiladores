#pragma once
#ifndef AST_HPP
#define AST_HPP
#include "Symbols.hpp"
#include <iostream>
#include <string>
#include <vector>
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
  ARG_LIST,
  EMPTY
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
};
#endif
