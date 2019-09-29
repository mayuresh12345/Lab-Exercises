%{
	#include "yac.tab.h"	
%}

%%
[a-zA-Z]+[a-zA-Z_]* {printf("Varname\n"); return varname;}
["int"|"float"|"char"|"double"] {printf("datatype\n"); return datatype;}
";" {printf("semicolon\n");return semicolon;}
"," {printf("comma\n");return comma;}
\n return NL;
%%

int yywrap()
{
	return 1;
}