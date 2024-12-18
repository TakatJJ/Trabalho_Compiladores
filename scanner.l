%{

  #include <map>
  #include <string>
  #include "Symbols.hpp"
  #include "parser.tab.hpp"
  using namespace std;

  int isRunningConstant = 1;
  int numberOfLines = 1;

  map<string, Symbol> symbols_table;


%}

%x COMMENT

%%
"char" {  return KW_CHAR;}
"int" { return KW_INT; }
"if" { return KW_IF; }
"then" { return KW_THEN; }
"else" { return KW_ELSE; }
"while" { return KW_WHILE; }
"read" { return KW_READ; }
"print" { return KW_PRINT; }
"return" { return KW_RETURN; }

[,;:()\[\]{}=+\-*/%<>&|~] { return yytext[0]; }

[a-zA-Z0-9]+ {

  if (symbols_table.find(yytext) == symbols_table.end()) {
    symbols_table[yytext] = Symbol(SYMBOL_IDENTIFIER, yytext);
  }
  yylval.symbol = &symbols_table[yytext];
  return TK_IDENTIFIER;
}

'.' {

  if (symbols_table.find(yytext) == symbols_table.end()) {
    symbols_table[yytext] = Symbol(SYMBOL_LIT_CHAR, yytext);
  }
  yylval.symbol = &symbols_table[yytext];
  return LIT_CHAR;
}


#[0-9]+ {

  if (symbols_table.find(yytext) == symbols_table.end()) {
    symbols_table[yytext] = Symbol(SYMBOL_LIT_INTEGER, yytext);
  }
  yylval.symbol = &symbols_table[yytext];
  return LIT_INT;
}


\"([^"\\]|\\.)*\" {

  if (symbols_table.find(yytext) == symbols_table.end()) {
    symbols_table[yytext] = Symbol(SYMBOL_LIT_STRING, yytext);
  }
  yylval.symbol = &symbols_table[yytext];
  return LIT_STRING;
}

"." { return TOKEN_ERROR; }
[\n] { numberOfLines++; }

 <<EOF>> {
  isRunningConstant = 0;
  return EOF;
}

"//".* {}

"/**" {BEGIN(COMMENT);}
<COMMENT>"**/" {BEGIN(INITIAL);}
<COMMENT>"\n" {numberOfLines++;}
<COMMENT>. {}


[ \t] {}
. {return TOKEN_ERROR;}

%%

#include <iostream>

int yywrap() {
  return 1;
}

int isRunning() { return isRunningConstant; }

void initMe() { return; }

int getLineNumber() { return numberOfLines; }

void printSymbolsTable() {
  for (map<string, Symbol>::iterator it = symbols_table.begin();
       it != symbols_table.end(); ++it) {
    cout << it->second.get_text() << " => " << it->second.get_type() << endl;
  }
}
