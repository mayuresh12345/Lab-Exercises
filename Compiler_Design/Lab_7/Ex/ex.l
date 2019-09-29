%{

	#include <stdio.h>
	#include <stdlib.h>
	#include "yac.tab.h"
%}

%%
[0-9]+ {printf("%s\n", yytext); return NUMBER;}
"$" {printf("NEWLINE\n"); return NL;}
[a-zA-Z]+ {printf("%s\n", yytext); return ID;}
"+" {printf("+\n"); return PLUS;}
"-" {printf("-\n"); return MINUS;}
%%

int yywrap()
{
	return 1;
}