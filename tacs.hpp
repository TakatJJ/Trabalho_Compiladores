#pragma once
#include "Symbols.hpp"
#include "AST.hpp"
#include <vector>

enum TAC_TYPE {
    TAC_SYMBOL,
    TAC_ADD,
    TAC_SUB,
    TAC_MUL,
    TAC_DIV,
    TAC_COPY,
    TAC_AND,
    TAC_OR,
    TAC_NOT,
    TAC_BIGGER,
    TAC_SMALLER,
    TAC_EQUAL,
    TAC_GOTO,
    TAC_IFZ,
    TAC_LABEL,
    TAC_PARAM,
    TAC_CALL,
    TAC_RETURN,
    TAC_BEGINFUNC,
    TAC_ENDFUNC,
    TAC_MOV,
    TAC_READ,
    TAC_WRITE,
    TAC_ARG,
    TAC_TEMP,
    TAC_FUNC,
    TAC_END
};

class TAC {
    public:
        TAC_TYPE type;
        Symbol* res;
        Symbol* op1;
        Symbol* op2;
        vector<TAC*> code;
        TAC(TAC_TYPE type, Symbol* res, Symbol* op1, Symbol* op2);
        static vector<TAC*> TAC_Join(vector<TAC*> first, vector<TAC*> second);
        static void TAC_Print(TAC* tac);
        static void TAC_Print(vector<TAC*> code);
        static vector<TAC*> TAC_Gen(AST* ast);
        static vector<TAC*> resolveTwoOPS(TAC_TYPE type, vector<vector<TAC*>> code);
        ~TAC();
};
