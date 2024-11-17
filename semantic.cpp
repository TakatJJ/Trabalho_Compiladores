#include "semantic.hpp"

int semantic_errors = 0;

void check_program(AST* node) {
    check_and_set_declarations(node);
    check_undeclared(node);
    // Mais coisas aqui abaixo depois
}

void check_and_set_declarations(AST* node) {
    if (node == nullptr) return;
    
    switch (node->type)
    {
        case ASTNodeType::DEC_VAR:
            if (node->symbol->get_type() != SYMBOL_IDENTIFIER){
                cout << "Semantic error: variable " << node->symbol->get_text() << " already declared" << endl;
                semantic_errors++;
            }
            else
            {
                node->symbol->set_type(SYMBOL_VAR);
                if (node->children[0]->type == ASTNodeType::INT)
                {
                    node->symbol->set_data_type(DATA_TYPE_INT);
                }
                else if (node->children[0]->type == ASTNodeType::CHAR)
                {
                    node->symbol->set_data_type(DATA_TYPE_CHAR);
                }
            }
                
            break;
        case ASTNodeType::DEC_FUNC:
            if (node->symbol->get_type() != SYMBOL_IDENTIFIER){
                cout << "Semantic error: function " << node->symbol->get_text() << " already declared" << endl;
                semantic_errors++;
            }
            else
            {
                node->symbol->set_type(SYMBOL_FUNC);
                if (node->children[0]->type == ASTNodeType::INT)
                {
                    node->symbol->set_data_type(DATA_TYPE_INT);
                }
                else if (node->children[0]->type == ASTNodeType::CHAR)
                {
                    node->symbol->set_data_type(DATA_TYPE_CHAR);
                }
            }
            break;
        case ASTNodeType::DEC_VECTOR:
            if (node->symbol->get_type() != SYMBOL_IDENTIFIER){
                cout << "Semantic error: vector " << node->symbol->get_text() << " already declared" << endl;
                semantic_errors++;
            }
            else
            {
                node->symbol->set_type(SYMBOL_VEC);
                if (node->children[0]->type == ASTNodeType::INT)
                {
                    node->symbol->set_data_type(DATA_TYPE_INT);
                }
                else if (node->children[0]->type == ASTNodeType::CHAR)
                {
                    node->symbol->set_data_type(DATA_TYPE_CHAR);
                }
            }
            break;
        case ASTNodeType::DEC_VECTOR_INIT:
            if (node->symbol->get_type() != SYMBOL_IDENTIFIER){
                cout << "Semantic error: vector " << node->symbol->get_text() << " already declared" << endl;
                semantic_errors++;
            }
            else
            {
                node->symbol->set_type(SYMBOL_VEC);
                if (node->children[0]->type == ASTNodeType::INT)
                {
                    node->symbol->set_data_type(DATA_TYPE_INT);
                }
                else if (node->children[0]->type == ASTNodeType::CHAR)
                {
                    node->symbol->set_data_type(DATA_TYPE_CHAR);
                }
            }
            break;
    }


    for (auto child : node->children) {
        check_and_set_declarations(child);
    }
}

void check_undeclared(AST* node) 
{
    return;
}