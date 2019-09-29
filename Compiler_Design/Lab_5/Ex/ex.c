#include <stdio.h>
#include <ctype.h>
#include "lex.yy.c"
#include <string.h>
struct token lookahead;
int i = 0;
void proc_t();
void proc_e()
{
	lookahead = getNextToken();
	if(strcmp(lookahead.lexemename, "NUMBER") == 0)
	{
		lookahead = getNextToken();
		proc_t();
	}
	else
		printf("\nError");
	if(strcmp(lookahead.lexemename, "EOL") == 0)
		printf("\nSuccessful");
	else
		printf("\nError");
}
void proc_t()
{
	lookahead = getNextToken();
	if(strcmp(lookahead.lexemename, "MUL") == 0)
	{
		lookahead = getNextToken();
		if(strcmp(lookahead.lexemename, "NUMBER") == 0)
		{
			lookahead = getNextToken();
			proc_t();
		}
		else
			printf("\nError");
	}
}
int main()
{
	lookahead = getNextToken();
	proc_e();
	return 0;
}