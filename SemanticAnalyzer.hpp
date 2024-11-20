#pragma once
#include "AST.hpp"
#include "Symbols.hpp"
#include <map>

extern map<string, Symbol> symbols_table;

class SemanticAnalyzer {
public:
  static void check_ast_semantic(AST *node);

private:
  static void check_and_set_declarations(AST *node);
  static void check_undeclared(AST *node);
  static pair<int, int> type_infer(AST *node);

  // Uitls:
  static bool valid_id(std::pair<int, int> expr, AST *p);
  static bool data_type_compatible(int datatype1, int datatype2);
  static bool is_integer_or_char(int datatype);
  static bool check_vector_elements(AST *node, int datatype);
  static bool check_vector_size_init(AST *node);
  static int remove_starting_symbol(string s);
};
