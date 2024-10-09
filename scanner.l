%{
    #include "tokens.h"
    bool isRunningConstant = true;
    int numberOfLines = 1;


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

\"(.)*\" {return LIT_STRING;}

[,;:()\[\]{}=+\-*/%<>&|~] {return yytext[0];}
[a-zA-Z0-9]+ {return TK_IDENTIFIER;}

#[0-9]+ {map[yytext] = LIT_INT; return LIT_INT;}
'.'     {map[yytext] = LIT_CHAR; return LIT_CHAR;}
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
