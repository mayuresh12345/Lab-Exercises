%{
	#include <stdio.h>
	int words = 0;
	int chars = 0;
	int blanks = 0;
	int lines = 0;
%}

%%
[a-zA-Z]+ {words++; chars += strlen(yytext);}
\n {chars++; lines++;}
" " blanks++;
. {chars++;}
%%

int main(int argc, char **argv)
{
	yylex();
	printf("%8d%8d%8d%8d\n", lines, words, chars, blanks);
}

int yywrap()
{
	return 1;
}