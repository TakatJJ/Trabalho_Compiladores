#include <iostream>
using namespace std;
#include "parser.tab.cpp"
int yyparse();
//lex.yy.h
int yylex();
void printSymbolsTable();
bool isRunning();
int getLineNumber();
int yyerror(const char *s);
extern char *yytext;
extern FILE *yyin;
int main (int argc, char *argv[])
{
    yyin = fopen(argv[1], "r");
    cout << "Token Text: " << argv[1] << " Number of files: "<< argc << endl;
    yyparse();
    cout<< "Compilation finished successfully" << endl;

    printSymbolsTable();
    return 0;
}