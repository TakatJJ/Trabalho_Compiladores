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
      // Handle
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
      return "error";
    result = ast_decompiler(ast->children[0]) + " = " +
             ast_decompiler(ast->children[1]);
    break;
  case ASSIGN_VECTOR:
    if (ast->children.size() < 3)
      return "error";
    result = ast_decompiler(ast->children[0]) + "[" +
             ast_decompiler(ast->children[1]) +
             "] = " + ast_decompiler(ast->children[2]);
    break;
  case RETURN:
    result = "return " + ast_decompiler(ast->children[0]) + ";\n";
    break;
  case READ:
    result = "read " + ast_decompiler(ast->children[0]) + ";\n";
    break;
  case WHILE:
    if (ast->children.size() < 2)
      return "error"; // Check size
    result = "while(" + ast_decompiler(ast->children[0]) + ")\n" +
             ast_decompiler(ast->children[1]) + "\n";
    break;
  case IF:
    if (ast->children.size() < 2)
      return "error"; // Check size
    result = "if(" + ast_decompiler(ast->children[0]) + ")then " +
             ast_decompiler(ast->children[1]) + "\n";
    break;
  case IF_ELSE:
    if (ast->children.size() < 3)
      return "error"; // Check size
    result = "if(" + ast_decompiler(ast->children[0]) + ")then " +
             ast_decompiler(ast->children[1]) + "\nelse " +
             ast_decompiler(ast->children[2]) + "\n";
    break;
  case VECTOR:
    if (ast->children.size() < 2)
      return "error"; // Check size
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
    result = ast_decompiler(ast->children[0]) + "[" +
             ast_decompiler(ast->children[1]) + "];\n";
    break;
  case DEC_VECTOR_INIT: {
    if (ast->children.size() < 2)
      return "error";
    result = ast_decompiler(ast->children[0]) + "[" +
             ast_decompiler(ast->children[1]) + "] = ";
    for (size_t i = 2; i < ast->children.size(); i++) {
      result += ast_decompiler(ast->children[i]);
    }
    result += ";\n";
    break;
  }
  case DEC_VAR:
    if (ast->children.size() < 3)
      return "error";
    result = ast_decompiler(ast->children[0]) + " " +
             ast_decompiler(ast->children[1]) + " = " +
             ast_decompiler(ast->children[2]) + ";\n";
    break;
  case PROGRAM: {
    for (auto cmd : ast->children) {
      result += ast_decompiler(cmd) + "\n";
    }
    result += "EOF\n";
    break;
  }
  case FUNC: {
    if (ast->children.size() < 4)
      return "error"; // Check size
    result = ast_decompiler(ast->children[0]) + " " +
             ast_decompiler(ast->children[1]) + "(" +
             ast_decompiler(ast->children[2]) + ")";
    result += ast_decompiler(ast->children[3]);
    break;
  }
  case VAR: {
    if (ast->children.size() < 2)
      return "error"; // Check size
    result = ast_decompiler(ast->children[0]) + " " +
             ast_decompiler(ast->children[1]);
    break;
  }
  case INIT: {
    for (auto init : ast->children) {
      result += ast_decompiler(init) + ",\n";
    }
    break;
  }
  case PARAM:
  case ARG_LIST: {
    for (auto arg : ast->children) {
      result += ast_decompiler(arg) + ", ";
    }
    break;
  }
  case PRINT:
    result = "PRINT";
    break;
  }
  return result;
}
