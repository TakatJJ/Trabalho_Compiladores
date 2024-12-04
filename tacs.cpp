#include "tacs.hpp"
#include <vector>

using namespace std;
TAC::TAC(TAC_TYPE type, Symbol *res, Symbol *op1, Symbol *op2)
{
    this->type = type;
    this->res = res;
    this->op1 = op1;
    this->op2 = op2;
}

vector<TAC *> TAC::TAC_Gen(AST *node)
{
    if (node == nullptr)
        return {};

    vector<vector<TAC *>> code;
    vector<TAC *> result;
    for (auto child : node->children)
    {
        code.push_back(TAC_Gen(child));
    }
    //cout << "Node type: " << AST::ast_type_to_string(node) << endl;
    switch (node->type)
    {
    case ASTNodeType::SYMBOL:
        result =  {new TAC(TAC_SYMBOL, node->symbol, nullptr, nullptr)};
        break;

        
    case ASTNodeType::NOT:
        result = resolveTwoOPS(TAC_NOT, code);
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
        for (auto c : code)
        {
            result = TAC_Join(result, c);
        }
        break;
    }
    return result;
}

vector<TAC *> TAC::TAC_Join(vector<TAC*> first, vector<TAC*> second)
{
    
    std::vector<TAC *> result;
    result.reserve(first.size() + second.size());  
    result.insert(result.end(), first.begin(), first.end());
    result.insert(result.end(), second.begin(), second.end());
    return result; 
    
}



void TAC::TAC_Print(TAC *tac)
{
    if (tac->type == TAC_SYMBOL)
        return;
    
    switch (tac->type)
    {
    case TAC_MUL: cout << "TAC_MUL: ";break;
    case TAC_SUB: cout << "TAC_SUB: ";break;
    case TAC_DIV: cout << "TAC_DIV: ";break;
    case TAC_BIGGER: cout << "TAC_BIGGER: ";break;
    case TAC_SMALLER: cout << "TAC_SMALLER: ";break;
    case TAC_EQUAL: cout << "TAC_EQUAL: ";break;
    case TAC_AND: cout << "TAC_AND: ";break;
    case TAC_OR: cout << "TAC_OR: ";break;
    case TAC_NOT: cout << "TAC_NOT: ";break;
    case TAC_ADD: cout << "TAC_ADD: ";break;
    default: cout << "TAC_UNKNOWN: ";break;
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

void TAC::TAC_Print(vector<TAC *> code)
{
    for (auto tac : code)
    {
        TAC_Print(tac);
    }
}

vector<TAC *> TAC::resolveTwoOPS(TAC_TYPE type, vector<vector<TAC *>> code)
{
    Symbol* op1 = code[0].back()->res? code[0].back()->res : nullptr;
    Symbol* op2 = code[1].back()->res? code[1].back()->res : nullptr;

    vector<TAC *> newExpr = {new TAC(type, Symbol::makeTemp(),op1,op2 )};


    vector<TAC *> result = TAC_Join(code[0], TAC_Join(code[1],newExpr));

    return result;
}