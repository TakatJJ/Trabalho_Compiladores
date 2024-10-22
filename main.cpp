#include <iostream>
using namespace std;

//lex.yy.h
int yylex();
void printSymbolsTable();
bool isRunning();
int getLineNumber();
extern char *yytext;
extern FILE *yyin;
int main (int argc, char *argv[])
{
    yyin = fopen(argv[1], "r");
    cout << "Token Text: " << argv[1] << " Number of files: "<< argc << endl;
    int token = yylex();
    while (isRunning() != 0)
    {   

        if(token == 290){
            cout << "[Erro Lexico] " << "Token: " << token << " Text: " << yytext << " Linha: " << getLineNumber() << endl;
        }
        else{

            cout << "Token: " << token << " Text: " << yytext << endl;

        }
        token = yylex();
    }
    cout << "Number of lines: " << getLineNumber() << endl;

    printSymbolsTable();
    return 0;
}