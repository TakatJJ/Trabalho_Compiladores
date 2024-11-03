#pragma once


#include "AST.hpp"

ofstream AST::file_decom("decompiled.txt");

AST::AST(ASTNodeType type, Symbol *symbol) {
            this->type = type;
            this->symbol = symbol;
        }
AST::AST(ASTNodeType type, vector<AST*> children) {
            this->type = type;
            this->children = children;
        }
AST::AST(ASTNodeType type) {
            this->type = type;
        }
AST::~AST() {
        for (AST* child : children) {
            delete child;
        }
        }
string AST::ast_decompiler (AST *ast) {
            if (ast == NULL) return "";

            switch (ast->type) {
                case ADD:{
                    file_decom << ast_decompiler(ast->children[0]) << " + " << ast_decompiler(ast->children[1]);
                    break;
                }
                case SUB:{
                    file_decom << ast_decompiler(ast->children[0]) << " - " << ast_decompiler(ast->children[1]);
                    break;
                }

                case DIV:{
                    file_decom << ast_decompiler(ast->children[0]) << " / " << ast_decompiler(ast->children[1]);
                    break;
                }
                case MULT:{
                    file_decom << ast_decompiler(ast->children[0]) << " * " << ast_decompiler(ast->children[1]);
                    break;
                }
                case SYMBOL:
                    return  ast->symbol->get_text();
                case BIGGER:{
                    file_decom << ast_decompiler(ast->children[0]) << " > " << ast_decompiler(ast->children[1]);
                    break;
                }
                case SMALLER:{
                    file_decom << ast_decompiler(ast->children[0]) << " < " << ast_decompiler(ast->children[1]);
                    break;
                }
                case EQUAL:{
                    file_decom << ast_decompiler(ast->children[0]) << " = " << ast_decompiler(ast->children[1]);
                    break;
                }
                case AND:{
                    file_decom << ast_decompiler(ast->children[0]) << " & " << ast_decompiler(ast->children[1]);
                    break;
                }
                case OR:{
                    file_decom << ast_decompiler(ast->children[0]) << " | " << ast_decompiler(ast->children[1]);
                    break;
                }
                case NOT:{
                    file_decom << '~' << ast_decompiler(ast->children[0]);
                    break;
                }
                case ASSIGN:{
                    file_decom << ast_decompiler(ast->children[0]) << " = " << ast_decompiler(ast->children[1]);
                    break;
                }
                case ASSIGN_VECTOR:{
                    file_decom << ast_decompiler(ast->children[0]) << "[" <<  ast_decompiler(ast->children[1]) << "]" << " = " << ast_decompiler(ast->children[2]);
                    break;
                }
                case RETURN:{
                    file_decom << "return" << ast_decompiler(ast->children[0]) << ";" << endl;
                    break;
                }
                    
                case READ:{
                    file_decom << "read" << ast_decompiler(ast->children[0]) << ";" << endl;
                    break;
                }
                case WHILE:{
                    file_decom << "while(" << ast_decompiler(ast->children[0]) << ")" << endl << ast_decompiler(ast->children[1]) << endl;
                    break;
                }
                case IF:{
                    file_decom << "if(" << ast_decompiler(ast->children[0]) << ")" << "then " << ast_decompiler(ast->children[1])   << endl;
                    break;
                }
                case IF_ELSE:{
                    file_decom << "if(" << ast_decompiler(ast->children[0]) << ")" << "then " << ast_decompiler(ast->children[1]) << endl << "else " << ast_decompiler(ast->children[2]) << endl;
                    break;
                }
                case VECTOR:{    
                    file_decom << ast_decompiler(ast->children[0]) << "[" << ast_decompiler(ast->children[1]) << "]";
                    break;
                }
                case INT:
                    return"int";
                case CHAR:
                    return "char";
                case BLOCK:{
                        file_decom << "{";
                     for( auto cmd : ast->children){
                            file_decom << ast_decompiler(cmd) << endl;
                     }
                        file_decom << "}" << endl;
                    break;

            }

               case FUNCALL:{
                    file_decom << ast_decompiler(ast->children[0]) <<"(" << ast_decompiler(ast->children[1])<< ")";
                    break;
               }

               case DEC_VECTOR:{
                    file_decom << ast_decompiler(ast->children[0]) << "[" << ast_decompiler(ast->children[1]) << "];" << endl;
                    break;
               }

               case DEC_VECTOR_INIT:{
                    file_decom << ast_decompiler(ast->children[0]) << "[" << ast_decompiler(ast->children[1]) << "]" << "=" ;

                   for(int i = 2; i < ast->children.size(); i++){
                            file_decom << ast_decompiler(ast->children[i]);
                    }

                    file_decom << ";" << endl;
                    break;
               }
               case DEC_VAR:{
                    file_decom << ast_decompiler(ast->children[0]) << " " << ast_decompiler(ast->children[1]) << " = " << ast_decompiler(ast->children[2]) << ";" << endl;
                    break;
               }

               case PROGRAM:{

                //    init_file();
                    string program = ""; 
                    for (auto cmd : ast->children){
                        file_decom << ast_decompiler(cmd) << endl;
                    }
                    file_decom << "EOF" << endl;
                    // close_file();
                    return "";
               }


               case FUNC:{
                    file_decom << ast_decompiler(ast->children[0]) << " " << ast_decompiler(ast->children[1]) <<  "(" << ast_decompiler(ast->children[2]) << ")";
                    file_decom << ast_decompiler(ast->children[3]);
               }
                   break;
               case VAR:{
                    file_decom << ast_decompiler(ast->children[0]) << " " << ast_decompiler(ast->children[1]);
               }
                   break;

               case INIT:{
                    for (auto init : ast->children){
                        file_decom << ast_decompiler(init) << "," << endl;
                    }
                    break;
                    }

               case PARAM:{
                    for (auto param : ast->children){
                        file_decom << ast_decompiler(param) << ", ";
                    }
                    break;
               }
                case ARG_LIST: {
                    for (auto arg : ast->children){
                        file_decom << ast_decompiler(arg) << ", ";
                    }
                    break;
                }
            } 
            return "";          
        }