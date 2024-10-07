#include <iostream>
using namespace std;

//lex.yy.h
int yylex();
extern char *yytext;
extern FILE *yyin;
int main (int argc, char *argv[])
{
    yyin = fopen(argv[1], "r");
    cout << "Token Text" << endl;
    cout << argc << endl;
    cout << argv[1] << endl;
    int token = yylex();
    while (token)
    {
        cout << "Token: " << token << " Text: " << yytext << endl;
        token = yylex();

    }
}