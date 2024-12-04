#pragma once
#include "AST.hpp"
#include "Symbols.hpp"
#include <vector>

enum TAC_TYPE {
  TAC_SYMBOL,  // PRONTO
  TAC_ADD,     // PRONTO
  TAC_SUB,     // PRONTO
  TAC_MUL,     // PRONTO
  TAC_DIV,     // PRONTO
  TAC_AND,     // PRONTO
  TAC_OR,      // PRONTO
  TAC_NOT,     // PRONTO
  TAC_BIGGER,  // PRONTO
  TAC_SMALLER, // PRONTO
  TAC_EQUAL,   // PRONTO
  TAC_IFZ,     // PRONTO
  TAC_LABEL,
  TAC_PARAM,
  TAC_CALL,
  TAC_RETURN,
  TAC_BEGINFUNC,
  TAC_ENDFUNC,
  TAC_MOVE, // PRONTO
  TAC_READ, // PRONTO
  TAC_ARG,
  TAC_FUNC,
  TAC_END,
  TAC_JUMP, // PRONTO
  TAC_PRINT // PRONTO
};

class TAC {
public:
  TAC_TYPE type;
  Symbol *res;
  Symbol *op1;
  Symbol *op2;
  vector<TAC *> code;
  TAC(TAC_TYPE type, Symbol *res, Symbol *op1, Symbol *op2);
  static vector<TAC *> TAC_Join(vector<TAC *> first, vector<TAC *> second);
  static void TAC_Print(TAC *tac);
  static void TAC_Print(vector<TAC *> code);
  static vector<TAC *> TAC_Gen(AST *ast);
  static vector<TAC *> resolveTwoOPS(TAC_TYPE type, vector<vector<TAC *>> code);
  static vector<TAC *> resolveNOT(vector<vector<TAC *>> code);
  static vector<TAC *> resolveIF(vector<vector<TAC *>> code);
  static vector<TAC *> resolveIFELSE(vector<vector<TAC *>> code);
  static vector<TAC *> resolveWHILE(vector<vector<TAC *>> code);
  static vector<TAC *> resolvePRINT(vector<vector<TAC *>> code);
  static vector<TAC *> resolveVECTOR_DEC_INIT(AST *node);
  static vector<TAC *> resolveARG_LIST(vector<vector<TAC *>> code);
  ~TAC();
};
