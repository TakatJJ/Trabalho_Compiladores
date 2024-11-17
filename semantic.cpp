#include <iostream>
#include <string>
#include "semantic.hpp"
#include "Symbols.hpp"

int semantic_errors = 0;

void check_semantic(AST* node) {
    check_and_set_declarations(node);
    check_undeclared(node);
    // Mais coisas aqui abaixo depois
}

void check_and_set_declarations(AST* node) {
    cout << "Checking node " << node->ast_type_to_string(node) << endl;
    if (node == nullptr) return;
    
    switch (node->type)
    {
        case ASTNodeType::DEC_VAR:
            if (node->children[1]->symbol->type != SYMBOL_IDENTIFIER){
                cout << "Semantic error: variable " << node->children[1]->symbol->get_text() << " already declared" << endl;
                semantic_errors++;
            }
            else
            {
                cout << "Variable " << node->children[1]->symbol->get_text() << " declared" << endl;
                node->children[1]->symbol->set_type(SYMBOL_VAR);
                if (node->children[0]->type == ASTNodeType::INT)
                {
                    node->children[1]->symbol->set_data_type(DATA_TYPE_INT);
                }
                else if (node->children[0]->type == ASTNodeType::CHAR)
                {
                    node->children[1]->symbol->set_data_type(DATA_TYPE_CHAR);
                }
            }
                
            break;
        case ASTNodeType::DEC_FUNC:
            if (node->children[1]->symbol->get_type() != SYMBOL_IDENTIFIER){
                cout << "Semantic error: function " << node->children[1]->symbol->get_text() << " already declared" << endl;
                semantic_errors++;
            }
            else
            {
                cout << "Function " << node->children[1]->symbol->get_text() << " declared" << endl;
                node->children[1]->symbol->set_type(SYMBOL_FUNC);
                if (node->children[0]->type == ASTNodeType::INT)
                {
                    node->children[1]->symbol->set_data_type(DATA_TYPE_INT);
                }
                else if (node->children[0]->type == ASTNodeType::CHAR)
                {
                    node->children[1]->symbol->set_data_type(DATA_TYPE_CHAR);
                }
            }
            break;
        case ASTNodeType::DEC_VECTOR:
            if (node->children[1]->children[0]->symbol->get_type() != SYMBOL_IDENTIFIER){
                cout << "Semantic error: vector " << node->children[1]->children[0]->symbol->get_text() << " already declared" << endl;
                semantic_errors++;
            }
            else
            {
                cout << "Vector " << node->children[1]->children[0]->symbol->get_text() << " declared" << endl;
                node->children[1]->children[0]->symbol->set_type(SYMBOL_VEC);
                if (node->children[0]->type == ASTNodeType::INT)
                {
                    node->children[1]->children[0]->symbol->set_data_type(DATA_TYPE_INT);
                }
                else if (node->children[0]->type == ASTNodeType::CHAR)
                {
                    node->children[1]->children[0]->symbol->set_data_type(DATA_TYPE_CHAR);
                }
            }
            break;
        case ASTNodeType::DEC_VECTOR_INIT:
            if (node->children[1]->children[0]->symbol->get_type() != SYMBOL_IDENTIFIER){
                cout << "Semantic error: vector " << node->children[1]->children[0]->symbol->get_text() << " already declared" << endl;
                semantic_errors++;
            }
            else
            {
                cout << "Vector " << node->children[1]->children[0]->symbol->get_text() << " declared" << endl;
                node->children[1]->children[0]->symbol->set_type(SYMBOL_VEC);
                if (node->children[0]->type == ASTNodeType::INT)
                {
                    node->children[1]->children[0]->symbol->set_data_type(DATA_TYPE_INT);
                }
                else if (node->children[0]->type == ASTNodeType::CHAR)
                {
                    node->children[1]->children[0]->symbol->set_data_type(DATA_TYPE_CHAR);
                }
            }
            break;
    }


    for (AST* child : node->children) {
        check_and_set_declarations(child);
    }
}

void check_undeclared(AST* node) 
{
    return;
}