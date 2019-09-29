%{
	#include "yac.tab.h"
%}

%%
"if" {printf("IF\n"); return IF;}
"else if" {printf("ELSE IF\n"); return ELSEIF;}
"else" {printf("ELSE\n"); return ELSE;}
\n {return NL;}
"(" {return LB;}
")" {return RB;}
[a-zA-Z][a-zA-Z_]* {return ID;}
[0-9][0-9]* {return NUM;}
"printf" {printf("Statement\n"); return statement;}
. {}
%%
int yywrap()
{
	return 1;
}


