#pragma once
#include "AST.hpp"
#include "Symbols.hpp"
#include <vector>

enum TAC_TYPE {
  TAC_SYMBOL,  // PRONTO
  TAC_ADD,     // PRONTO FEITO NA ASM
  TAC_SUB,     // PRONTO FEITO NA ASM
  TAC_MUL,     // PRONTO FEITO NA ASM
  TAC_DIV,     // PRONTO FEITO NA ASM
  TAC_AND,     // PRONTO
  TAC_OR,      // PRONTO
  TAC_NOT,     // PRONTO
  TAC_BIGGER,  // PRONTO FEITO NA ASM
  TAC_SMALLER, // PRONTO FEITO NA ASM
  TAC_EQUAL,   // PRONTO FEITO NA ASM
  TAC_IFZ,     // PRONTO
  TAC_LABEL,
  TAC_PARAM,
  TAC_CALL,
  TAC_RET,
  TAC_DEC,
  TAC_VEC, // FEITO NA ASM
  TAC_VEC_WRITE,
  TAC_BEGINFUNC,
  TAC_ENDFUNC,
  TAC_MOVE, // PRONTO FEITO NA ASM
  TAC_READ, // PRONTO
  TAC_ARG,
  TAC_JUMP, // PRONTO
  TAC_PRINT // PRONTO  FEITO NA ASM
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
  static vector<TAC *> resolveDEC_FUNC(vector<vector<TAC *>> code);
  ~TAC();
};
