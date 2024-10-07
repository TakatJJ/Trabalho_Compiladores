%%
"int" {return 1;}
"char" {return 2;}
[ ] {}
%%
#include <iostream>
using namespace std;


int yywrap ()
{
    return 0;
}

int isRunning() 
{
    if (yytext[0] == EOF)
        return 0;
    return 1;
}