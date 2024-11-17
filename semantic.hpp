#pragma once
#include "Symbols.hpp"
#include "AST.hpp"

extern int semantic_errors;

void check_semantic(AST* node);

void check_and_set_declarations(AST* node);
void check_undeclared(AST* node);
