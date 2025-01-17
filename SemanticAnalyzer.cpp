#include "SemanticAnalyzer.hpp"
#include "AST.hpp"
#include "Symbols.hpp"
#include <iostream>
#include <string>

void SemanticAnalyzer::check_ast_semantic(AST *node) {
  check_and_set_declarations(node);
  check_undeclared(node);
  type_infer(node);
  // Mais coisas aqui abaixo depois
}

void SemanticAnalyzer::check_and_set_declarations(AST *node) {
  // cout << "Checking node " << node->ast_type_to_string(node) << endl;
  if (node == nullptr)
    return;

  switch (node->type) {
  case ASTNodeType::DEC_VAR:
    if (node->children[1]->symbol->type != SYMBOL_IDENTIFIER) {
      cout << "Semantic error: variable "
           << node->children[1]->symbol->get_text() << " already declared"
           << endl;
      exit(4);
    } else {
      cout << "Variable " << node->children[1]->symbol->get_text()
           << " declared" << endl;
      node->children[1]->symbol->set_type(SYMBOL_VAR);
      if (node->children[0]->type == ASTNodeType::INT) {
        node->children[1]->symbol->set_data_type(DATA_TYPE_INT);
      } else if (node->children[0]->type == ASTNodeType::CHAR) {
        node->children[1]->symbol->set_data_type(DATA_TYPE_CHAR);
      }

      if (!data_type_compatible(node->children[1]->symbol->get_data_type(),
                                node->children[2]->symbol->get_data_type())) {
        cout << "Semantic error: variable "
             << node->children[1]->symbol->get_text()
             << " declared with incompatible data type" << endl;
        exit(4);
      }
    }

    break;
  case ASTNodeType::DEC_FUNC:
    if (node->children[1]->symbol->get_type() != SYMBOL_IDENTIFIER) {
      cout << "Semantic error: function "
           << node->children[1]->symbol->get_text() << " already declared"
           << endl;
      exit(4);
    } else {
      cout << "Function " << node->children[1]->symbol->get_text()
           << " declared" << endl;

      node->children[1]->symbol->set_type(SYMBOL_FUNC);
      node->children[1]->symbol->param_count =
          node->children[2]->children.size();

      if (node->children[0]->type == ASTNodeType::INT) {
        node->children[1]->symbol->set_data_type(DATA_TYPE_INT);
      } else if (node->children[0]->type == ASTNodeType::CHAR) {
        node->children[1]->symbol->set_data_type(DATA_TYPE_CHAR);
      }
    }
    break;
  case ASTNodeType::DEC_VECTOR:
    if (node->children[1]->children[0]->symbol->get_type() !=
        SYMBOL_IDENTIFIER) {
      cout << "Semantic error: vector "
           << node->children[1]->children[0]->symbol->get_text()
           << " already declared" << endl;
      exit(4);
    } else {
      cout << "Vector " << node->children[1]->children[0]->symbol->get_text()
           << " declared" << endl;

      node->children[1]->children[0]->symbol->set_type(SYMBOL_VEC);
      node->children[1]->children[0]->symbol->vector_size =
          remove_starting_symbol(
              node->children[1]->children[1]->symbol->get_text());

      if (node->children[0]->type == ASTNodeType::INT) {
        node->children[1]->children[0]->symbol->set_data_type(DATA_TYPE_INT);
      } else if (node->children[0]->type == ASTNodeType::CHAR) {
        node->children[1]->children[0]->symbol->set_data_type(DATA_TYPE_CHAR);
      }
    }
    break;
  case ASTNodeType::DEC_VECTOR_INIT:
    if (node->children[1]->children[0]->symbol->get_type() !=
        SYMBOL_IDENTIFIER) {
      cout << "Semantic error: vector "
           << node->children[1]->children[0]->symbol->get_text()
           << " already declared" << endl;
      exit(4);
    } else {
      cout << "Vector " << node->children[1]->children[0]->symbol->get_text()
           << " declared" << endl;
      node->children[1]->children[0]->symbol->set_type(SYMBOL_VEC);

      if (!check_vector_size_init(node)) {
        cout << "Semantic error: vector "
             << node->children[1]->children[0]->symbol->get_text()
             << " declared with incompatible size" << endl;
        exit(4);
      }
      node->children[1]->children[0]->symbol->vector_size =
          remove_starting_symbol(
              node->children[1]->children[1]->symbol->get_text().c_str());

      if (node->children[0]->type == ASTNodeType::INT) {
        node->children[1]->children[0]->symbol->set_data_type(DATA_TYPE_INT);
      } else if (node->children[0]->type == ASTNodeType::CHAR) {
        node->children[1]->children[0]->symbol->set_data_type(DATA_TYPE_CHAR);
      }
      if (!check_vector_elements(
              node->children[2],
              node->children[1]->children[0]->symbol->get_data_type())) {
        cout << "Semantic error: vector "
             << node->children[1]->children[0]->symbol->get_text()
             << " declared with incompatible data type" << endl;
        exit(4);
      }
    }
    break;
  case ASTNodeType::PARAM:
    if (node->children[1]->symbol->get_type() != SYMBOL_IDENTIFIER) {
      cout << "Semantic error: parameter "
           << node->children[1]->symbol->get_text() << " already declared"
           << endl;
      exit(4);
    } else {
      cout << "Parameter " << node->children[1]->symbol->get_text()
           << " declared" << endl;
      node->children[1]->symbol->set_type(SYMBOL_VAR);
      if (node->children[0]->type == ASTNodeType::INT) {
        node->children[1]->symbol->set_data_type(DATA_TYPE_INT);
      } else if (node->children[0]->type == ASTNodeType::CHAR) {
        node->children[1]->symbol->set_data_type(DATA_TYPE_CHAR);
      }
    }
    break;
  }
  for (AST *child : node->children) {
    check_and_set_declarations(child);
  }
}

void SemanticAnalyzer::check_undeclared(AST *node) {
  // cout << "Checking node " << node->ast_type_to_string(node) << endl;

  if (node == nullptr)
    return;

  if (node->type == ASTNodeType::SYMBOL) {
    if (node->symbol->get_type() == SYMBOL_IDENTIFIER) {
      cout << "Semantic error: undeclared identifier "
           << node->symbol->get_text() << endl;
      exit(4);
    }
  }

  for (AST *child : node->children) {
    check_undeclared(child);
  }
}

bool SemanticAnalyzer::data_type_compatible(int datatype1, int datatype2) {
  if (datatype1 == datatype2)
    return true;
  else if (is_integer_or_char(datatype1) && is_integer_or_char(datatype2))
    return true;
  else
    return false;
}

bool SemanticAnalyzer::is_integer_or_char(int datatype) {
  if (datatype == DATA_TYPE_INT || datatype == DATA_TYPE_CHAR)
    return true;
  else
    return false;
}
bool SemanticAnalyzer::check_vector_elements(AST *node, int data_type) {
  for (AST *child : node->children) {
    if (data_type_compatible(child->symbol->get_data_type(), data_type) == 0) {
      cout << "Element " << child->symbol->get_text()
           << " has incompatible data type" << endl;
      return false;
    }
  }
  return true;
}

bool SemanticAnalyzer::check_vector_size_init(AST *node) {
  cout << node->children[2]->children.size() << endl;
  if (remove_starting_symbol(
          node->children[1]->children[1]->symbol->get_text()) !=
      node->children[2]->children.size())
    return false;
  else
    return true;
}

int SemanticAnalyzer::remove_starting_symbol(string s) {
  s = s.substr(1);
  return stoi(s);
}

bool SemanticAnalyzer::valid_id(std::pair<int, int> expr, AST *p) {

  if (expr.first == SYMBOL_VEC && !(p->type == VECTOR)) {
    fprintf(stderr, "VEC NOT INDEXED:%d second: %d\n", expr.first, expr.second);
    exit(4);
  }

  if (expr.first == SYMBOL_FUNC && !(p->type == FUNCALL)) {
    fprintf(stderr, "FUNC ISOLED:%d second: %d\n", expr.first, expr.second);
    exit(4);
  }
  return true;
}
std::pair<int, int> SemanticAnalyzer::type_infer(AST *node) {
  // cout << "Checking node in INFER:" << node->ast_type_to_string(node) << endl;
  ASTNodeType node_type = node->type;

  switch (node_type) {

  case ASTNodeType::SYMBOL:
    return std::make_pair(node->symbol->type, node->symbol->data_type);

  // Arithmetic expressions
  case ASTNodeType::ADD:
  case ASTNodeType::SUB:
  case ASTNodeType::DIV:
  case ASTNodeType::MULT: {
    std::pair<int, int> left = type_infer(node->children[0]);
    std::pair<int, int> right = type_infer(node->children[1]);

    valid_id(left, node->children[0]);
    valid_id(left, node->children[1]);

    if (is_integer_or_char(left.second) && is_integer_or_char(right.second)) {
      return std::make_pair(0, DATA_TYPE_INT); // Return int type
    }
    fprintf(stderr, "Type mismatch in arithmetic operation.\n");
    exit(4);
  }

  // Comparasion expressions
  case ASTNodeType::BIGGER:
  case ASTNodeType::SMALLER:
  case ASTNodeType::EQUAL: {
    std::pair<int, int> left = type_infer(node->children[0]);
    std::pair<int, int> right = type_infer(node->children[1]);

    valid_id(left, node->children[0]);
    valid_id(left, node->children[1]);

    if (is_integer_or_char(left.second) && is_integer_or_char(right.second)) {
      return std::make_pair(0, DATA_TYPE_BOOL); // Comparison should return bool
    }
    fprintf(stderr, "Invalid types for comparison.\n");
    exit(4);
  }

  // Boolean expressions
  case ASTNodeType::AND:
  case ASTNodeType::OR: {
    std::pair<int, int> left = type_infer(node->children[0]);
    std::pair<int, int> right = type_infer(node->children[1]);

    if (left.second == DATA_TYPE_BOOL && right.second == DATA_TYPE_BOOL)
      return std::make_pair(0, DATA_TYPE_BOOL);

    fprintf(stderr, "Logical operations require boolean operands.\n");
    exit(4);
  }

  case ASTNodeType::NOT: {
    std::pair<int, int> child = type_infer(node->children[0]);

    if (child.second == DATA_TYPE_BOOL) {
      return std::make_pair(0, DATA_TYPE_BOOL); // NOT operation returns bool
    }

    fprintf(stderr, "NOT operation requires a boolean operand.\n");
    exit(4);
  }

  case ASTNodeType::ASSIGN: {
    std::pair<int, int> left = type_infer(node->children[0]);

    if (left.first != SYMBOL_VAR) {
      fprintf(stderr, "Assigned variable must be a symbol variable.\n");
      exit(4);
    }

    std::pair<int, int> right = type_infer(node->children[1]);

    valid_id(right, node->children[1]);

    if (is_integer_or_char(right.second)) {
      return std::make_pair(0, 0);
    }

    fprintf(stderr, "Cannot assign non-integer or non-char type.\n");
    exit(4);
  }

  case ASTNodeType::ASSIGN_VECTOR: {
    std::pair<int, int> id = type_infer(node->children[0]);

    if (id.first != SYMBOL_VEC) {
      fprintf(stderr, "Assigned symbol must be a vector.\n");
      exit(4);
    }

    std::pair<int, int> expr = type_infer(node->children[1]);
    std::pair<int, int> assign_expr = type_infer(node->children[2]);

    if (is_integer_or_char(expr.second) &&
        is_integer_or_char(assign_expr.second)) {
      return std::make_pair(0, 0);
    }

    fprintf(stderr, "Type mismatch in vector assignment.\n");
    exit(4);
  }

  case ASTNodeType::RETURN: {
    std::pair<int, int> expr = type_infer(node->children[0]);

    valid_id(expr, node->children[0]);

    if (is_integer_or_char(expr.second)) {
      return std::make_pair(0, 0);
    }

    fprintf(stderr, "Return type must be integer or char.\n");
    exit(4);
  }

  case ASTNodeType::PRINT: {
    for (auto p : node->children) {

      std::pair<int, int> expr = type_infer(p);
      if (!((expr.first == SYMBOL_LIT_STRING) ||
            is_integer_or_char(expr.second))) {
        fprintf(stderr, "NOT LIT STRING OR INT OR CHAR first:%d second: %d\n",
                expr.first, expr.second);
        exit(4);
      }

      valid_id(expr, p);
    }
    return std::make_pair(0, 0);
  }
  case ASTNodeType::READ: {
    std::pair<int, int> child = type_infer(node->children[0]);

    if (child.first != SYMBOL_VAR) {
      fprintf(stderr, "READ operation requires a variable symbol.\n");
      exit(4);
    }

    return std::make_pair(0, 0);
  }

  case ASTNodeType::WHILE: {
    std::pair<int, int> condition = type_infer(node->children[0]);
    std::pair<int, int> block = type_infer(node->children[1]);

    if (condition.second == DATA_TYPE_BOOL) {
      return std::make_pair(0, 0); // WHILE block returns void
    }

    fprintf(stderr, "Condition in WHILE must be boolean.\n");
    exit(4);
  }

  case ASTNodeType::IF: {
    std::pair<int, int> condition = type_infer(node->children[0]);
    std::pair<int, int> then_block = type_infer(node->children[1]);

    if (condition.second == DATA_TYPE_BOOL) {
      return std::make_pair(0, 0); // IF block returns void
    }

    fprintf(stderr, "Condition in IF must be boolean.\n");
    exit(4);
  }

  case ASTNodeType::IF_ELSE: {
    std::pair<int, int> condition = type_infer(node->children[0]);
    std::pair<int, int> then_block = type_infer(node->children[1]);
    std::pair<int, int> else_block = type_infer(node->children[2]);

    if (condition.second == DATA_TYPE_BOOL) {
      return std::make_pair(0, 0); // IF-ELSE block returns void
    }

    fprintf(stderr, "Condition in IF-ELSE must be boolean.\n");
    exit(4);
  }

  case ASTNodeType::VECTOR: {
    std::pair<int, int> id = type_infer(node->children[0]);

    if (id.first != SYMBOL_VEC) {
      fprintf(stderr, " Not a vec.\n");
      exit(4);
    }

    std::pair<int, int> expr = type_infer(node->children[1]);
    if (!is_integer_or_char(expr.second)) {
      fprintf(stderr, "Not into compatible indexing vector\n");
      exit(4);
    }

    return id;
  }

  case ASTNodeType::BLOCK: {
    for (auto cmd : node->children) {
      std::pair<int, int> result = type_infer(cmd);
    }
    return std::make_pair(0, 0);
  }

  case ASTNodeType::FUNCALL: {
    std::pair<int, int> id = type_infer(node->children[0]);

    if (id.first != SYMBOL_FUNC) {
      fprintf(stderr, "Function call must refer to a function.\n");
      exit(4);
    }

    Symbol *fun_symbol = node->children[0]->symbol;

    if (fun_symbol->param_count != (int)node->children[1]->children.size()) {
      fprintf(stderr, "Invalid argument number for function call.\n");
      exit(4);
    }

    std::pair<int, int> arg_list = type_infer(node->children[1]);
    return std::make_pair(SYMBOL_FUNC,
                          fun_symbol->data_type); // Return function type
  }

  case ASTNodeType::PROGRAM: {
    // Iterate over all statements in the program
    for (auto cmd : node->children) {
      std::pair<int, int> result = type_infer(cmd);
    }
    return std::make_pair(0, 0); // Return void for program
  }

  case ASTNodeType::DEC_FUNC:
    type_infer(node->children[3]);
    return std::make_pair(0, 0); // Declare function

  case ASTNodeType::ARG_LIST: {

    for (auto cmd : node->children) {
      std::pair<int, int> arg = type_infer(cmd);

      if (!is_integer_or_char(arg.second)) {
        fprintf(stderr, "Invalid parameter type.\n");
        exit(4);
      }
    }
    return std::make_pair(0, 0); // Return type for argument list
  }

  case ASTNodeType::EMPTY:
    return std::make_pair(0, 0); // Empty statement has no effect

  // Definitons handled in check_and_set_declarations
  case ASTNodeType::INT:
  case ASTNodeType::CHAR:
  case ASTNodeType::DEC_VECTOR:
  case ASTNodeType::DEC_VECTOR_INIT:
  case ASTNodeType::DEC_VAR:
  case ASTNodeType::INIT:
  case ASTNodeType::PARAM:
    return std::make_pair(0, 0); // Return types as needed
                                 //
  default:
    fprintf(stderr, "Unknown AST node type.\n");
    return std::make_pair(-1, -1); // Error case
  }

  return std::make_pair(-1, -1); // Default return value
}
