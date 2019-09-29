#include <stdio.h>
#include "lex.yy.c"
#include <ctype.h>
#include <string.h>
struct token lookahead;
int i = 0;
void proc_S();
void proc_T();
void proc_T1();
void proc_S()
{
	lookahead = getNextToken();
	if(strcmp(lookahead.lexemename, "a") == 0 || strcmp(lookahead.lexemename, ">") == 0)
	{
		lookahead = getNextToken();
	}
	else if(strcmp(lookahead.lexemename, "(") == 0)
	{
		proc_T();
		lookahead = getNextToken();
		if(strcmp(lookahead.lexemename, ")") == 0)
			lookahead = getNextToken();
		else
			printf("Reject\n");
	}
	if(strcmp(lookahead.lexemename, "EOL") == 0 || lookahead == NULL)
		printf("Success\n");
}
void proc_T()
{
	proc_S();
	proc_T1();
}
void proc_T1()
{
	if(strcmp(lookahead.lexemename, ",") == 0)
	{
		lookahead = getNextToken();
		proc_S();
		proc_T1();
	}
}
int main()
{
	yyin = fopen("input.c", "r");
	lookahead = getNextToken();
	proc_S();
	printf("Reject\n");
}