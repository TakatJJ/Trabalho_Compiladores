#include "AST.hpp"
#include <memory>
#include <string>
#include <vector>

using namespace std;

AST::AST(ASTNodeType type, Symbol *symbol) : type(type), symbol(symbol) {}

AST::AST(ASTNodeType type, vector<AST *> children)
    : type(type), children(move(children)) {}

AST::AST(ASTNodeType type) : type(type) {}

AST::~AST() {
  for (AST *child : children) {
    delete child;
  }
  delete symbol;
}
void AST::print_ast(AST *ast, int level) {
  if (ast == NULL)
    return;
  for (int i = 0; i < level; i++)
    cout << "  " << level;
  switch (ast->type) {
  case ADD:
    cout << "ADD" << endl;
    break;
  case SUB:
    cout << "SUB" << endl;
    break;
  case DIV:
    cout << "DIV" << endl;
    break;
  case MULT:
    cout << "MULT" << endl;
    break;
  case SYMBOL:
    cout << "SYMBOL: " << ast->symbol->get_type() << ast->symbol->get_text()
         << endl;
    break;
  case BIGGER:
    cout << "BIGGER" << endl;
    break;
  case SMALLER:
    cout << "SMALLER" << endl;
    break;
  case EQUAL:
    cout << "EQUAL" << endl;
    break;
  case AND:
    cout << "AND" << endl;
    break;
  case OR:
    cout << "OR" << endl;
    break;
  case NOT:
    cout << "NOT" << endl;
    break;
  case ASSIGN:
    cout << "ASSIGN" << endl;
    break;
  case ASSIGN_VECTOR:
    cout << "ASSIGN_VECTOR" << endl;
    break;
  case RETURN:
    cout << "RETURN" << endl;
    break;
  case READ:
    cout << "READ" << endl;
    break;
  case WHILE:
    cout << "WHILE" << endl;
    break;
  case IF:
    cout << "IF" << endl;
    break;
  case IF_ELSE:
    cout << "IF_ELSE" << endl;
    break;
  case VECTOR:
    cout << "VECTOR" << endl;
    break;
  case INT:
    cout << "INT" << endl;
    break;
  case CHAR:
    cout << "CHAR" << endl;
    break;
  case BLOCK:
    cout << "BLOCK" << endl;
    break;
  case FUNCALL:
    cout << "FUNCALL" << endl;
    break;
  case DEC_VECTOR:
    cout << "DEC_VECTOR" << endl;
    break;
  case DEC_VECTOR_INIT:
    cout << "DEC_VECTOR_INIT" << endl;
    break;
  case DEC_VAR:
    cout << "DEC_VAR" << endl;
    break;
  case PROGRAM:
    cout << "PROGRAM" << endl;
    break;
  case DEC_FUNC:
    cout << "DEC_FUNC" << endl;
    break;
  case INIT:
    cout << "INIT" << endl;
    break;
  case PARAM:
    cout << "PARAM" << endl;
    break;
  case PARAMLIST:
    cout << "PARAMLIST" << endl;
    break;
  case ARG_LIST:
    cout << "ARG_LIST" << endl;
    break;

  case PRINT:
    cout << "PRINT" << endl;
    break;

  case EMPTY:
    cout << "EMPTY" << endl;
    break;
  }
  for (AST *child : ast->children) {
    print_ast(child, level + 1);
  }
}

string AST::ast_decompiler(AST *ast) {
  if (!ast)
    return "";

  string result;
  switch (ast->type) {
  case ADD:
  case SUB:
  case DIV:
  case MULT:
  case BIGGER:
  case SMALLER:
  case EQUAL:
  case AND:
  case OR: {
    if (ast->children.size() < 2) {
      return "error";
    }
    string op = (ast->type == ADD)       ? " + "
                : (ast->type == SUB)     ? " - "
                : (ast->type == DIV)     ? " / "
                : (ast->type == MULT)    ? " * "
                : (ast->type == BIGGER)  ? " > "
                : (ast->type == SMALLER) ? " < "
                : (ast->type == EQUAL)   ? " = "
                : (ast->type == AND)     ? " & "
                                         : " | ";
    result = ast_decompiler(ast->children[0]) + op +
             ast_decompiler(ast->children[1]);
    break;
  }
  case SYMBOL:
    return ast->symbol->get_text();
  case NOT:
    result = "~" + ast_decompiler(ast->children[0]);
    break;
  case ASSIGN:
    if (ast->children.size() < 2)
      return "assign error";
    result = ast_decompiler(ast->children[0]) + " = " +
             ast_decompiler(ast->children[1]) + ";";
    break;
  case ASSIGN_VECTOR:
    if (ast->children.size() < 3)
      return "assign vector error";
    result = ast_decompiler(ast->children[0]) + "[" +
             ast_decompiler(ast->children[1]) +
             "] = " + ast_decompiler(ast->children[2]) + ";";
    break;
  case RETURN:
    result = "return " + ast_decompiler(ast->children[0]) + ";\n";
    break;
  case READ:
    result = "read " + ast_decompiler(ast->children[0]) + ";\n";
    break;
  case WHILE:
    if (ast->children.size() < 2)
      return "while error";
    result = "while(" + ast_decompiler(ast->children[0]) + ")\n" +
             ast_decompiler(ast->children[1]) + "\n";
    break;
  case IF:
    if (ast->children.size() < 2)
      return "if error";
    result = "if(" + ast_decompiler(ast->children[0]) + ")then " +
             ast_decompiler(ast->children[1]) + "\n";
    break;
  case IF_ELSE:
    if (ast->children.size() < 3)
      return "if else error";
    result = "if(" + ast_decompiler(ast->children[0]) + ")then " +
             ast_decompiler(ast->children[1]) + "\nelse " +
             ast_decompiler(ast->children[2]) + "\n";
    break;
  case VECTOR:
    if (ast->children.size() < 2)
      return "vector error";
    result = ast_decompiler(ast->children[0]) + "[" +
             ast_decompiler(ast->children[1]) + "]";
    break;
  case INT:
    return "int";
  case CHAR:
    return "char";
  case BLOCK: {
    result = "{\n";
    for (auto cmd : ast->children) {
      result += ast_decompiler(cmd) + "\n";
    }
    result += "}\n";
    break;
  }
  case FUNCALL:
    if (ast->children.size() < 2)
      return "error";
    result = ast_decompiler(ast->children[0]) + "(" +
             ast_decompiler(ast->children[1]) + ")";
    break;
  case DEC_VECTOR:

    if (ast->children.size() < 2)
      return "error";

    result = ast_decompiler(ast->children[0]) + " " +
             ast_decompiler(ast->children[1]) + ";\n";
    break;

  case DEC_VECTOR_INIT: {

    if (ast->children.size() < 2)
      return "error";

    result = ast_decompiler(ast->children[0]) + " " +
             ast_decompiler(ast->children[1]) + " = ";

    for (size_t i = 2; i < ast->children.size(); i++) {
      result += ast_decompiler(ast->children[i]);
    }

    result += ";\n";

    break;
  }
  case DEC_VAR:
    if (ast->children.size() < 3)
      return "dec var error";
    result = ast_decompiler(ast->children[0]) + " " +
             ast_decompiler(ast->children[1]) + " = " +
             ast_decompiler(ast->children[2]) + ";\n";
    break;
  case PROGRAM: {
    for (auto cmd : ast->children) {
      result += ast_decompiler(cmd) + "\n";
    }
    result += "";
    break;
  }
  case DEC_FUNC: {
    if (ast->children.size() < 3)
      return "func error";
    result = ast_decompiler(ast->children[0]) + " "+ ast_decompiler(ast->children[1]) 
             + "(" + ast_decompiler(ast->children[2]) + ")";
    result += ast_decompiler(ast->children[3]);
    break;
  }
  case INIT: {
    for (auto init : ast->children) {
      result += ast_decompiler(init) + " ";
    }
    break;
  }
  case PARAMLIST:{
    if (ast->children.size() < 0)
      return "error_paramlist";

    if (ast->children.size() > 1){
      result += ast_decompiler(ast->children[0]);
      for (size_t i = 1; i < ast->children.size(); i++) {
        result += ", " + ast_decompiler(ast->children[i]);
      }
    }
    else {
      for (auto param : ast->children) {
        result += ast_decompiler(param);
      }
    }
    break;
  }
  case PARAM:{
    if (ast->children.size() < 0)
      return "error_param";

    result += ast_decompiler(ast->children[0]) + " " + ast_decompiler(ast->children[1]);
    break;
  }
    break;
  case ARG_LIST: {

    if (ast->children.size() < 0)
      return "error_arg_list";

    result += ast_decompiler(ast->children[0]);
    for (size_t i = 1; i < ast->children.size(); i++) {
      result += ", " + ast_decompiler(ast->children[i]);
    }
    break;
  }
  case PRINT:

    if (ast->children.size() < 0)
      return "print error";

    result += "print " + ast_decompiler(ast->children[0]);

    for (size_t i = 1; i < ast->children.size(); i++) {
      result += " " + ast_decompiler(ast->children[i]);
    }

    result += ";\n";
    break;
  case EMPTY:
    result = ";";
    break;
  }

  return result;
}

string AST::ast_type_to_string (AST* node) 
{
    switch (node->type)
    {
        case ADD:
            return "ADD";
        case SUB:
            return "SUB";
        case DIV:
            return "DIV";
        case MULT:
            return "MULT";
        case SYMBOL:
            return "SYMBOL";
        case BIGGER:
            return "BIGGER";
        case SMALLER:
            return "SMALLER";
        case EQUAL:
            return "EQUAL";
        case AND:
            return "AND";
        case OR:
            return "OR";
        case NOT:
            return "NOT";
        case ASSIGN:
            return "ASSIGN";
        case ASSIGN_VECTOR:
            return "ASSIGN_VECTOR";
        case RETURN:
            return "RETURN";
        case PRINT:
            return "PRINT";
        case READ:
            return "READ";
        case WHILE:
            return "WHILE";
        case IF:
            return "IF";
        case IF_ELSE:
            return "IF_ELSE";
        case VECTOR:
            return "VECTOR";
        case INT:
            return "INT";
        case CHAR:
            return "CHAR";
        case BLOCK:
            return "BLOCK";
        case FUNCALL:
            return "FUNCALL";
        case DEC_VECTOR:
            return "DEC_VECTOR";
        case DEC_VECTOR_INIT:
            return "DEC_VECTOR_INIT";
        case DEC_VAR:
            return "DEC_VAR";
        case PROGRAM:
            return "PROGRAM";
        case DEC_FUNC:
            return "DEC_FUNC";
        case INIT:
            return "INIT";
        case PARAMLIST:
            return "PARAMLIST";
        case PARAM:
            return "PARAM";
        case ARG_LIST:
            return "ARG_LIST";
        case EMPTY:
            return "EMPTY";
    }
    return "";
}