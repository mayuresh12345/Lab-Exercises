%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#define YY_DECL struct token *yylex(void)

	struct token
	{
		char lexeme[100];
		int index;
		int rowno, colno;
		char type[100];
	};
	int lineno = 1, colno = 1;

	struct token *tk;
	struct token *allocToken()
	{
		struct token* tk;
		tk = (struct token*)malloc(sizeof(struct token));
		tk->index = -1;
		return tk;
	}

	void tkSet(struct token* tk, char lexeme[100], int index, int rowno, int colno, char type[100])
	{
		if(tk == NULL)
			return;
		strcpy(tk->lexeme, lexeme);
		tk->index = index;
		tk->rowno = rowno;
		tk->colno = colno;
		strcpy(tk->type, type);
	}

%}
%%

"/*"(.(\n?))*"*/" {
	int i = 0;
	while(yytext[i] != '\0')
	{
		if(yytext[i] == '\n')
		{
			lineno++;
			colno = 1;
		}
		else
			colno++;
		i++;
	}
}

"#include".*"\n" {lineno++; colno = 1;}
"#define".*"\n" {lineno++; colno = 1;}

"//".*"\n" {lineno++; colno = 1;}

(\"(.)*\") {
	tk = allocToken();
	char type[100] = "LITERAL";
	tkSet(tk, "", -1, lineno, colno, type);
	colno += strlen(yytext);
	return tk;
}

(\'(.)\') {
	tk = allocToken();
	char type[100] = "LITERAL";
	tkSet(tk, "", -1, lineno, colno, type);
	colno += strlen(yytext);
	return tk;
}

\n {lineno++; colno = 1;}
\t {colno += 4;}

("="|"<"|">")"="? {
	tk = allocToken();
	char type[100] = "RELATIONAL";
	tkSet(tk, yytext, -1, lineno, colno, type);
	colno += strlen(yytext);
	return tk;
}

"!=" {
	tk = allocToken();
	char type[100] = "RELATIONAL";
	tkSet(tk, yytext, -1, lineno, colno, type);
	colno += strlen(yytext);
	return tk;
}

("+"|"-"|"*"|"/")^("+"|"-"|"*"|"/") {
	tk = allocToken();
	char type[100] = "ARITHMETIC";
	tkSet(tk, yytext, -1, lineno, colno, type);
	colno += strlen(yytext);
	return tk;
}

("&"&?|"|"\|?) {
	tk = allocToken();
	char type[100] = "LOGICAL";
	tkSet(tk, yytext, -1, lineno, colno, type);
	colno += strlen(yytext);
	return tk;
}

("++"|"--"|"&"|"~") {
	tk = allocToken();
	char type[100] = "UNARY";
	tkSet(tk, yytext, -1, lineno, colno, type);
	colno += strlen(yytext);
	return tk;
}

("+="|"-="|"*="|"\=") {
	tk = allocToken();
	char type[100] = "SHORTHAND";
	tkSet(tk, yytext, -1, lineno, colno, type);
	colno += strlen(yytext);
	return tk;
}

(-0*[1-9][0-9]*)|(\+?0*[1-9][0-9]*)|(-0*[1-9][0-9]*\.[0-9]+)|(\+?0*[1-9][0-9]*\.[0-9]+) {
	tk = allocToken();
	char type[100] = "NUMERICAL";
	tkSet(tk, yytext, -1, lineno, colno, type);
	colno += strlen(yytext);
	return tk;	
}

(","|"{"|"}"|";"|"("|")"|"["|"]") {
	tk = allocToken();
	char type[100] = "SPECIAL CHARACTER";
	tkSet(tk, yytext, -1, lineno, colno, type);
	colno += strlen(yytext);
	return tk;	
}

[^a-zA-Z0-9_]"int"|"char"|"return"|"for"|"if"|"else"[^a-zA-Z0-9_] {
	tk = allocToken();
	char type[100] = "KEYWORD";
	tkSet(tk, yytext, -1, lineno, colno, type);
	colno += strlen(yytext);
	return tk;		
}
[a-zA-Z_][a-zA-Z_0-9]* {
	tk = allocToken();
	char type[100] = "IDENTIFIER";
	tkSet(tk, yytext, -1, lineno, colno, type);
	colno += strlen(yytext);
	return tk;	
}

%%

void getNextToken()
{
	while(tk == yylex())
	{
		printf("< %s, %d, %d, %s >", tk->lexeme, tk->rowno, tk->colno, tk->type);
		return;
	}
}

int main()
{
	yyin = fopen("input.c", "r");
	yyout = fopen("output.c", "w");

	while(1)
	{
		printf("1) GetNextToken\t2) Exit\n");
		int ch;
		scanf("%d", &ch);

		if(ch == 1)
			getNextToken();
		else
			break;
	}
}

int yywrap()
{
	return 1;
}