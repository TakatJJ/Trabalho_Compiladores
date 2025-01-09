#pragma once
#include <vector>
#include <fstream>
#include <map>
#include "tacs.hpp"
#include "Symbols.hpp"
extern map<string, Symbol> symbols_table;
class ASM {
public:
    static void generate_ASM(vector<TAC*> tacs);
    static string generate_temp(string asm_code);
    static string generate_variables(string asm_code, vector<TAC*> tacs);
    static string create_asm_variable(TAC* tac);
    static string create_asm_vector(TAC* tac);
    static string create_asm_vector_empty(TAC* tac);
    static string cleanVectorIndex(string text);
    static string generate_literals(string asm_code);
    static string resolveSymbol(Symbol* symbol);
    static string resolveVecIndex (Symbol *symbol);
    static string makeImediate (Symbol *symbol);
};
