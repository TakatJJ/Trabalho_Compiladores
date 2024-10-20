#include <iostream>
using namespace std;
#include "parser.tab.cpp"
#include "parser.tab.hpp"
int yyparse();
//lex.yy.h
int yylex();
void printSymbolsTable();
bool isRunning();
int getLineNumber();
int yyerror(const char *s);
extern char *yytext;
extern FILE *yyin;


string getTokenCLass(int token){
    switch(token){
        case KW_CHAR:
            return "KW_CHAR";
        case KW_INT:
            return "KW_INT";
        case KW_IF:
            return "KW_IF";
        case KW_THEN:
            return "KW_THEN";
        case KW_ELSE:
            return "KW_ELSE";
        case KW_WHILE:
            return "KW_WHILE";
        case KW_READ:
            return "KW_READ";
        case KW_PRINT:
            return "KW_PRINT";
        case KW_RETURN:
            return "KW_RETURN";
        case TK_IDENTIFIER:
            return "TK_IDENTIFIER";
        case LIT_INT:
            return "LIT_INT";
        case LIT_CHAR:
            return "LIT_CHAR";
        case LIT_STRING:
            return "LIT_STRING";
        case TOKEN_ERROR:
            return "TOKEN_ERROR";
        case EOF:
            return "EOF";
        default:
            return "UNKNOW";
    }
}
int main (int argc, char *argv[])
{
    yyin = fopen(argv[1], "r");
    cout << "Token Text: " << argv[1] << " Number of files: "<< argc << endl;

    // while(isRunning()){
    //     int tok = yylex();
    //     cout << "Token: " << getTokenCLass(tok) << " Number : " << tok << " Text: " << yytext << " Line: " << getLineNumber() << endl;
    // }
    yyparse();
    cout<< "Compilation finished successfully" << endl;

    printSymbolsTable();
    return 0;
}