%{
	#include <stdio.h>
	int v = 0;
	int c = 0;
%} 

%%
[aeiou] {v++;}
[a-zA-Z] {c++;}
%%

main(int argc, char **argv)
{
	yylex();
	printf("Vowels = %d\tConsonants = %d\n", v, c);
}

int yywrap()
{
	return 1;
}