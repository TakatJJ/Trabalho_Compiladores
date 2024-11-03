#include <iostream>
using namespace std;


extern int yylex();
extern int yyparse();
void printSymbolsTable();
bool isRunning();
int getLineNumber();
extern int yyerror(const char *s);
extern char *yytext;
extern FILE *yyin;

int main(int argc, char *argv[]) {
  yyin = fopen(argv[1], "r");
  cout << "Token Text: " << argv[1] << " Number of files: " << argc << endl;
  
  yyparse();
  cout << "Compilation finished successfully" << endl;

  printSymbolsTable();
  return 0;
}
