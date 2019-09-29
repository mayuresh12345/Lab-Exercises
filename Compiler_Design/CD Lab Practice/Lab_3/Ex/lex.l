%{
	int chars = 0;
	int words = 0;
	int lines = 0;
%}

%%
[a-zA-Z]+ {words++; chars = strlen(yytext);}
\n {lines++; chars++;}
. {chars++;}
%%

int main()
{
	yylex();
	printf("Words : %d\tChars = %d\tLines = %d\n", words, chars, lines);
}

int yywrap()
{
	return 1;
}