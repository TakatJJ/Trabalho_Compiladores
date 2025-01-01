#pragma once
#include <vector>
#include "tacs.hpp"
#include "Symbols.hpp"
#include <map>
extern map<string, Symbol> symbols_table;
class ASM {
public:
    static void generate_ASM(vector<TAC*> tacs);
    static string generate_literals(string asm_code);
    static string resolveSymbol(Symbol* symbol);
};
