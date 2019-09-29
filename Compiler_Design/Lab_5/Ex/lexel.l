%{
	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>
	#include "symboltable.h"
	#define YY_DECL Tokenptr yylex(void)

	int l=1, c=1, scope=0, fa=0;
	char dtype[10];
	Tokenptr tp;
	Tokenptr allocToken()
	{
		Tokenptr tp;
		tp = (Tokenptr)malloc(sizeof(struct Token));
		tp -> lexeme = (char*)malloc(20*sizeof(char));
		tp -> index = 0;
		tp -> type = EOFILE;
		return tp;
	}
	void setTokenArgs(Tokenptr tp, char *lexeme, int row, int col, enum tokenType type)
	{
		if(tp==NULL)
			return;
		strcpy(tp->lexeme, lexeme);
		tp->row = row;
		tp->col = col;
		tp->type = type;
	}
	char* getType(enum tokenType t)
	{
		switch(t)
		{
			case 0: return "LITERAL";
			case 1: return "KEYWORD";
			case 2: return "NUMBER";
			case 3: return "IDENTIFIER";
			case 4: return "SYMBOL";
			case 5: return "AOP";
			case 6: return "LOP";
			case 7: return "RELOP";
			case 8: return "FUNCTION";
			default: return "";
		}
	}
	void printToken(Tokenptr tp)
	{
		printf("<%s, %d, %d, %d, %s>\n", tp->lexeme, tp->row, tp->col, tp->index, getType(tp->type));
	}
%}
%%
"#"(.)*"\n" {
	l++;
}
"//"(.)*"\n" {
	l++;
}
"/*"([^*]|"*"[^/])*"*/"  {
	for(int i=0; i<yyleng; i++)
		if(yytext[i]=='\n')
		{
			l++;
			c=1;
		}
}
\"[^\"]*\" {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, LITERAL);
	c+=yyleng;
	return tp;
}
"int"|"char"|"if"|"else"|"while"|"void"|"for"|"return"|"float"|"double" {
	if(strcmp(yytext, "int") == 0||strcmp(yytext, "char") == 0||strcmp(yytext, "float") == 0||strcmp(yytext, "double") == 0 ||strcmp(yytext, "void") == 0)
		strcpy(dtype, yytext);
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, KEYWORD);
	c+=yyleng;
	return tp;
}
[a-zA-Z_][a-zA-Z0-9_]* {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, IDENTIFIER);
	c+=yyleng;
	return tp;
}
[+|-]?[0-9]+(.[0-9]+)?(E[+|-]?[0-9]+)? {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, NUMBER);
	c+=yyleng;
	return tp;
}
"+"|"-"|"*"|"/"|"%"|"+="|"-="|"*="|"/="|"%="|"++"|"--" {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, AOP);
	c+=yyleng;
	return tp;
}
"&"|"|"|"&&"|"||"|"!" {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, LOP);
	c+=yyleng;
	return tp;
}
">"|"<"|"!="|">="|"<="|"==" {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, RELOP);
	c+=yyleng;
	return tp;
}
\t|" " {
    c++;
}
\n {
	l++;
	c=1;
}
. {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, SYMBOL);
	if(strcmp(yytext, ";")==0)
		dtype[0]='\0';
	else if(yytext[0] == '{')
		scope++;
	else if(yytext[0] == '}')
		scope--;	
	c++;
	return tp;
}
%%
int main(int argc, char **argv)
{
	yyin = fopen("input.c", "r");
	Tokenptr tk;
	printf("<Lexeme, Row, Col, Index, Type>\n");
	while(tk = yylex())
	{
		printToken(tk);
		if(tk -> type == IDENTIFIER)
		{
			char tempdt[10];
			strcpy(tempdt, dtype);
			Tokenptr temp = yylex();
			printToken(temp);
			if(strcmp(temp -> lexeme, "(") == 0)
			{
				// if(dtype[0] == '\0')
				// 	break;
				char args[10][100];
				int i = 0;
				while(strcmp(temp -> lexeme, ")")!=0)
				{
					temp = yylex();
					printToken(temp);
					if(temp -> type == IDENTIFIER || temp -> type == LITERAL || temp -> type == NUMBER)
					{
						strcpy(args[i], temp ->lexeme);
						i++;
					}
					if(temp -> type == KEYWORD)
					{
						strcpy(dtype, temp -> lexeme);
					}
					if(temp -> type == IDENTIFIER)
					{
						temp -> index = Insert(temp, 0, dtype, scope, NULL, '\0');
					}
				}
				tk -> index = Insert(tk, 1, tempdt, scope, args, i);
				dtype[0] = '\0';
			}
			else
				tk -> index = Insert(tk, 0, tempdt, scope, NULL, '\0');
		}
	}
	fclose(yyin);
	Display();
	return 0;
}
int yywrap()
{
	return 1;
}
