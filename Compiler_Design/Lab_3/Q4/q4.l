%{
	#include <stdio.h>
	int sc = 0;
	int pf = 0;
%}

%%
"scanf" {sc++; fputs("READ", yyout);}
"printf" {pf++; fputs("WRITE", yyout);}
%%
int main(int argc, char **argv)
{
	yyin = fopen("input.c", "r");
	yyout = fopen("output.c", "w");
	yylex();
	printf("Scanf's = %d\tPrintf's = %d\n", sc, pf);
}
int yywrap()
{
	return 1;
}