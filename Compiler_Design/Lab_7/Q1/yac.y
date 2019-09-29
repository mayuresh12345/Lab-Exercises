%{
	#include <stdio.h>
	#include <stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}

%token datatype varname comma semicolon NL

%%
stmt : exp 
	;

exp : datatype V1 semicolon exp
	|
	;
V1 : varname comma V1
	| varname
	;

%% 
int yyerror(char *msg)
{
	printf("Invalid Expression\n");
	return 1;
}

void main()
{
	printf("Enter the expression\n");
	yyin = fopen("in.txt", "r");
	// yyin = stdin;
do{
	if(yyparse())	
	{
		printf("\nFailure");
		exit(0);
	}
	}
	while(!feof(yyin));
	printf("Success");
	
}

