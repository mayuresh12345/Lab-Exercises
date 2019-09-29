%{
	#include <stdio.h>
	int and = 0;
	int or = 0;
%}

%%
" and " {and++;}
" or " {or++;}
%%

int main(int argc, char** argv[])
{
	yylex();
	if(and > 0 || or > 0)
		printf("Compound Statement\n");
	else
		printf("Not a compound Statement\n");
}
int yywrap()
{
	return 1;
}