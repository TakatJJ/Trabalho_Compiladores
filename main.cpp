#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

extern int yylex();
extern int yyparse();
void printSymbolsTable();
bool isRunning();
int getLineNumber();
extern int yyerror(const char *s);
extern char *yytext;
extern FILE *yyin;
extern string decompiled_text;

int main(int argc, char *argv[]) {
  yyin = fopen(argv[1], "r");
  cout << "Token Text: " << argv[1] << " Number of files: " << argc << endl;
  yyparse();
  cout << "Compilation finished successfully" << endl;

  ofstream output_file(argv[2]);
  output_file << decompiled_text;
  output_file.close();
  printSymbolsTable();
  return 0;
}
