#include "tacs.hpp"
#include "AST.hpp"
#include <string>
#include <vector>

using namespace std;
TAC::TAC(TAC_TYPE type, Symbol *res, Symbol *op1, Symbol *op2) {
  this->type = type;
  this->res = res;
  this->op1 = op1;
  this->op2 = op2;
}

vector<TAC *> TAC::TAC_Gen(AST *node) {
  if (node == nullptr)
    return {};

  vector<vector<TAC *>> code;
  vector<TAC *> result;
  for (auto child : node->children) {
    code.push_back(TAC_Gen(child));
  }

  switch (node->type) {
  case ASTNodeType::SYMBOL:
    result = {new TAC(TAC_SYMBOL, node->symbol, nullptr, nullptr)};
    break;

  case ASTNodeType::DEC_VAR:
    result = {new TAC(TAC_DEC, node->children[1]->symbol,
                      node->children[2]->symbol, nullptr)};
    break;

  case ASTNodeType::DEC_VECTOR:
    result = {new TAC(TAC_DEC, node->children[1]->children[0]->symbol,
                      node->children[1]->children[1]->symbol, nullptr)};
    break;

  case ASTNodeType::DEC_VECTOR_INIT:
    result = TAC::resolveVECTOR_DEC_INIT(node);
    break;

  case ASTNodeType::ASSIGN:
    result = TAC_Join(code[1], {new TAC(TAC_MOVE, node->children[0]->symbol,
                                        code[1].back()->res, nullptr)});
    break;

  case ASTNodeType::ASSIGN_VECTOR:
    result = TAC_Join(code[1], code[2]);
    result =
        TAC_Join(result, {new TAC(TAC_VEC_WRITE, node->children[0]->symbol,
                                  code[1].back()->res, code[2].back()->res)});
    break;

  case ASTNodeType::READ:
    result = {new TAC(TAC_READ, node->children[0]->symbol, nullptr, nullptr)};
    break;
  case ASTNodeType::FUNCALL:
  // cout << "AAAAAAAAAAAAAAAAAAAA" << node->children[0]->symbol->get_text() << " TYPE: "<< node->children[0]->symbol->get_data_type()<< endl;
    result = TAC_Join(code[1], {new TAC(TAC_CALL, Symbol::makeTemp(node->children[0]->symbol->get_data_type()),
                                        node->children[0]->symbol, nullptr)});
    break;

    // case ASTNodeType::PARAMLIST:

    // break;
  case ASTNodeType::PARAM:
    result = {new TAC(TAC_PARAM, code[1].back()->res, nullptr, nullptr)};
    break;

  case ASTNodeType::DEC_FUNC:
    result = resolveDEC_FUNC(code);
    break;

  case ASTNodeType::VECTOR:
  // cout <<"AAAAAAAAAAAAAAA" <<node->children[0]->symbol->get_text()<<" TYPE: "<< node->children[0]->symbol->get_data_type()<< endl;
    result =
        TAC_Join(code[1], {new TAC(TAC_VEC, Symbol::makeTemp(node->children[0]->symbol->get_data_type()),
                                   code[0].back()->res, code[1].back()->res)});
    break;
  case ASTNodeType::RETURN:
    result = TAC_Join(
        code[0], {new TAC(TAC_RET, code[0].back()->res, nullptr, nullptr)});
    break;
  case ASTNodeType::ARG_LIST:
    result = resolveARG_LIST(code);
    break;

  case ASTNodeType::PRINT:
    result = resolvePRINT(code);
    break;
  case ASTNodeType::WHILE:
    result = resolveWHILE(code);
    break;

  case ASTNodeType::IF:
    result = resolveIF(code);
    break;
  case ASTNodeType::IF_ELSE:
    result = resolveIFELSE(code);
    break;

  case ASTNodeType::NOT:
    result = resolveNOT(code);
    break;
  case ASTNodeType::MULT:
    result = resolveTwoOPS(TAC_MUL, code);
    break;
  case ASTNodeType::SUB:

    result = resolveTwoOPS(TAC_SUB, code);
    break;
  case ASTNodeType::DIV:

    result = resolveTwoOPS(TAC_DIV, code);
    break;
  case ASTNodeType::ADD:
    result = resolveTwoOPS(TAC_ADD, code);
    break;
  case ASTNodeType::AND:
    result = resolveTwoOPS(TAC_AND, code);
    break;

  case ASTNodeType::OR:
    result = resolveTwoOPS(TAC_OR, code);
    break;
  case ASTNodeType::SMALLER:
    result = resolveTwoOPS(TAC_SMALLER, code);
    break;

  case ASTNodeType::BIGGER:
    result = resolveTwoOPS(TAC_BIGGER, code);
    break;

  case ASTNodeType::EQUAL:
    result = resolveTwoOPS(TAC_EQUAL, code);
    break;

  default:
    for (auto c : code) {
      result = TAC_Join(result, c);
    }
    break;
  }
  return result;
}

vector<TAC *> TAC::TAC_Join(vector<TAC *> first, vector<TAC *> second) {

  std::vector<TAC *> result;
  result.reserve(first.size() + second.size());
  result.insert(result.end(), first.begin(), first.end());
  result.insert(result.end(), second.begin(), second.end());
  return result;
}

void TAC::TAC_Print(TAC *tac) {
  if (tac->type == TAC_SYMBOL)
    return;

  switch (tac->type) {

  case TAC_DEC:
    cout << "TAC_DEC: ";
    break;
  case TAC_VEC:
    cout << "TAC_VEC: ";
    break;
  case TAC_VEC_WRITE:
    cout << "TAC_VEC_WRITE: ";
    break;
  case TAC_READ:
    cout << "TAC_READ: ";
    break;

  case TAC_ENDFUNC:

    cout << "TAC_ENDFUC: ";
    break;

  case TAC_BEGINFUNC:
    cout << "TAC_BEGINFUNC: ";
    break;

  case TAC_PARAM:
    cout << "TAC_PARAM: ";
    break;

  case TAC_RET:
    cout << "TAC_RET: ";
    break;
  case TAC_ARG:
    cout << "TAC_ARG: ";
    break;

  case TAC_MUL:
    cout << "TAC_MUL: ";
    break;
  case TAC_SUB:
    cout << "TAC_SUB: ";
    break;
  case TAC_DIV:
    cout << "TAC_DIV: ";
    break;
  case TAC_BIGGER:
    cout << "TAC_BIGGER: ";
    break;
  case TAC_SMALLER:
    cout << "TAC_SMALLER: ";
    break;
  case TAC_EQUAL:
    cout << "TAC_EQUAL: ";
    break;
  case TAC_AND:
    cout << "TAC_AND: ";
    break;
  case TAC_OR:
    cout << "TAC_OR: ";
    break;
  case TAC_NOT:
    cout << "TAC_NOT: ";
    break;
  case TAC_ADD:
    cout << "TAC_ADD: ";
    break;
  case TAC_MOVE:
    cout << "TAC_MOVE: ";
    break;
  case TAC_IFZ:
    cout << "TAC_IFZ: ";
    break;
  case TAC_LABEL:
    cout << "TAC_LABEL: ";
    break;
  case TAC_JUMP:
    cout << "TAC_JUMP: ";
    break;
  case TAC_PRINT:
    cout << "TAC_PRINT: ";
    break;
  case TAC_CALL:
    cout << "TAC_CALL: ";
    break;
  default:
    cout << "TAC_UNKNOWN: ";
    break;
  }
  if (tac->res != nullptr)
    cout << tac->res->get_text() << ",";
  if (tac->op1 != nullptr)
    cout << tac->op1->get_text() << ",";
  if (tac->op2 != nullptr)
    cout << tac->op2->get_text() << ",";

  cout << endl;
  return;
}

void TAC::TAC_Print(vector<TAC *> code) {
  for (auto tac : code) {
    TAC_Print(tac);
  }
}

vector<TAC *> TAC::resolveTwoOPS(TAC_TYPE type, vector<vector<TAC *>> code) {
  Symbol *op1 = code[0].back()->res ? code[0].back()->res : nullptr;
  Symbol *op2 = code[1].back()->res ? code[1].back()->res : nullptr;

  vector<TAC *> newExpr = {new TAC(type, Symbol::makeTemp(), op1, op2)};
  vector<TAC *> result = TAC_Join(code[0], TAC_Join(code[1], newExpr));

  return result;
}

vector<TAC *> TAC::resolveNOT(vector<vector<TAC *>> code) {
  Symbol *op1 = code[0].back()->res ? code[0].back()->res : nullptr;

  vector<TAC *> newExpr = {new TAC(TAC_NOT, Symbol::makeTemp(), op1, nullptr)};
  vector<TAC *> result = TAC_Join(code[0], newExpr);
  return result;
}

vector<TAC *> TAC::resolveIF(vector<vector<TAC *>> code) {

  Symbol *symbol = Symbol::makeLabel();
  vector<TAC *> result;

  vector<TAC *> tacIF = TAC_Join(
      code[0],
      {new TAC(TAC_IFZ, symbol, code[0].back()->res, nullptr)}); // TESTE
  result = TAC_Join(tacIF, code[1]);
  vector<TAC *> tacGoto = {new TAC(TAC_LABEL, symbol, nullptr, nullptr)};
  result = TAC_Join(result, tacGoto);
  return result;
  // if else
}

vector<TAC *> TAC::resolveWHILE(vector<vector<TAC *>> code) {

  Symbol *init_label = Symbol::makeLabel();
  Symbol *end_label = Symbol::makeLabel();

  vector<TAC *> tacINIT = {new TAC(TAC_LABEL, init_label, nullptr, nullptr)};
  vector<TAC *> result;

  result = TAC_Join(tacINIT, code[0]);
  result = TAC_Join(result, {new TAC(TAC_IFZ, end_label, result.back()->res,
                                     nullptr)}); // TESTE
  result = TAC_Join(result, code[1]);
  result = TAC_Join(result, {new TAC(TAC_JUMP, init_label, nullptr, nullptr)});
  result = TAC_Join(result, {new TAC(TAC_LABEL, end_label, nullptr, nullptr)});

  return result;
}

vector<TAC *> TAC::resolveIFELSE(vector<vector<TAC *>> code) {

  Symbol *else_label = Symbol::makeLabel();
  Symbol *end_label = Symbol::makeLabel();
  vector<TAC *> result;

  vector<TAC *> tacIF = TAC_Join(
      code[0],
      {new TAC(TAC_IFZ, else_label, code[0].back()->res, nullptr)}); // TESTE
  result = TAC_Join(tacIF, code[1]); // CODE[0] IF {CODE[1] JUMP}
  result = TAC_Join(result, {new TAC(TAC_JUMP, end_label, nullptr, nullptr)});

  vector<TAC *> tacElse = {new TAC(TAC_LABEL, else_label, nullptr, nullptr)};
  result = TAC_Join(result, tacElse);
  result = TAC_Join(result, code[2]);

  vector<TAC *> tacEND = {new TAC(TAC_LABEL, end_label, nullptr, nullptr)};
  result = TAC_Join(result, tacEND);
  return result;
}

vector<TAC *> TAC::resolvePRINT(vector<vector<TAC *>> code) {

  vector<TAC *> result = {};
  for (auto c : code) {
    result = TAC_Join(result, TAC_Join(c, {new TAC(TAC_PRINT, c.back()->res,
                                                   nullptr, nullptr)}));
  }

  return result;
}

vector<TAC *> TAC::resolveVECTOR_DEC_INIT(AST *node) {

  vector<TAC *> result = {};
  vector<AST *> lit_list = node->children[2]->children;
  Symbol *id = node->children[1]->children[0]->symbol;

  for (int i = 0; i < lit_list.size(); i++) {
    std::string index = "#" + to_string(i);
    result = TAC_Join(result, {new TAC(TAC_DEC, id, lit_list[i]->symbol,
                                       new Symbol(SYMBOL_LIT_INTEGER, index))});
  }

  return result;
}

vector<TAC *> TAC::resolveARG_LIST(vector<vector<TAC *>> code) {

  vector<TAC *> result = {};
  vector<TAC *> args = {};
  int i = 0;
  for (auto c : code) {
    Symbol *index = new Symbol(SYMBOL_LIT_INTEGER, "#" + to_string(i));
    result = TAC::TAC_Join(result, c);
    TAC *arg = c.back();
    TAC *new_arg = new TAC(TAC_ARG, arg->res, index, nullptr);
    args.push_back(new_arg);
    i++;
  }

  result = TAC::TAC_Join(result, args);

  return result;
}

vector<TAC *> TAC::resolveDEC_FUNC(vector<vector<TAC *>> code) {

  vector<TAC *> result = {};

  Symbol *id = code[1].back()->res;
  TAC *begin_func = new TAC(TAC_BEGINFUNC, id, nullptr, nullptr);
  int i = 0;

  for (auto c : code[2]) {
    // cout << "_______________________" << "PARAM: ";
    Symbol *index = new Symbol(SYMBOL_LIT_INTEGER, "#" + to_string(i));
    c->op1 = index;
    i++;
  }
  result = TAC_Join({begin_func}, code[2]);
  result = TAC_Join(result, code[3]);
  result = TAC_Join(result, {new TAC(TAC_ENDFUNC, id, nullptr, nullptr)});
  return result;
}
