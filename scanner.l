%{
    #include "tokens.h"
    bool isRunningConstant = true;
    int numberOfLines = 1;
%}


%x COMMENT


%%
[ \t]*(char)[ \t]* {return KW_CHAR;}
int {return KW_INT;}
[ \t]*(if)[ \t(]* {return KW_IF;}
[ \t]*(then)[ \t(]* {return KW_THEN;}
[ \t]*(else)[ \t(]* {return KW_ELSE;}
[ \t]*(while)[ \t(]* {return KW_WHILE;}
[ \t]*(read)[ \t]* {return KW_READ;}
[ \t]*(print)[ \t(]* {return KW_PRINT;}
[ \t]*(return)[ \t(;]* {return KW_RETURN;}
[,;:()\[\]{}=+\-*/%<>&|~] {return yytext[0];}


[ \t]*[a-zA-Z0-9]+[ \t]* {return TK_IDENTIFIER;}
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
