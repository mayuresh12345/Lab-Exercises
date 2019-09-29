%{
	#include <stdio.h>
	#include <stdlib.h>
	#define YY_DECL struct token* yylex(void)

	int v = 0;
	int c = 0;
%}

%%

[aeiouAEIOU] {v++;}
[a-zA-Z] {c++;}
. {}

%%

int main()
{
	yylex();
	printf("Vowels : %d\tConsonants : %d\n", v, c);
}

int yywrap()
{
	return 1;
}