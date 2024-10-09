%{
    #include "tokens.h"
    #include <string>
    #include <map>
    using namesapce std;
    bool isRunningConstant = true;
    int numberOfLines = 1;


    map<string, int> symbols_table;

    
%}


%x COMMENT



%%
"char" {return KW_CHAR;}
"int" {return KW_INT;}
"if"  {return KW_IF;}
"then" {return KW_THEN;}
"else" {return KW_ELSE;}
"while" {return KW_WHILE;}
"read" {return KW_READ;}
"print" {return KW_PRINT;}
"return" {return KW_RETURN;}


[,;:()\[\]{}=+\-*/%<>&|~] {return yytext[0];}

[a-zA-Z0-9]+ {symbols_table[yytext] = TK_IDENTIFIER; return TK_IDENTIFIER;}

#[0-9]+ {symbols_table[yytext] = LIT_INT; LIT_INT;}
'.'     {symbols_table[yytext] = LIT_CHAR; return LIT_CHAR;}

\"([^\"\n\\]|\\.)*\" {symbols_table[yytext] = LIT_STRING; return LIT_STRING;}
\"([^\"\n\\]|\\.)*\"(.\")+ {return TOKEN_ERROR;}
"."    {return TOKEN_ERROR;}
[\n]    {numberOfLines++;}


<<EOF>> {isRunningConstant = false; return 9;}
"//".* {}
"/**" {BEGIN(COMMENT); }
<COMMENT>"**/" {BEGIN(INITIAL);}
<COMMENT>"\n" {numberOfLines++;}
<COMMENT>. {}


[ \t] {}
. {return TOKEN_ERROR;}
%%

#include <iostream>
using namespace std;


int yywrap ()
{
    return 1;
}

bool isRunning() 
{
    return isRunningConstant;
}

void initMe()
{
    return;
}
int getLineNumber()
{
    return numberOfLines;
}
