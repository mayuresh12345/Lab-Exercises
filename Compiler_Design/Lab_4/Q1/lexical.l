%{
  #include <stdio.h>
  #include "symbolTable.h"
  #define YY_DECL token* yylex(void)

  int rownum = 1;
  int colnum = 1;
  token* tk;
  token* alloctoken()
  {
    token* t;
    t = (token *)malloc(sizeof(token));
    t->index = 0;
    t->row = 0;
    t->col = 0;
    t->type = EOFile;
    return t;
  }

  void setTokenargs(token* tk, char *lexemename, int index, int row, int col, enum tokentype type)
  {
    if(tk == NULL)
      return;
    strcpy(tk->lexemename, lexemename);
    tk->index = index;
    tk->row = row;
    tk->col = col;
    tk->type = type;
  }
%}

%%
"/*"[.|\n]*"*/" {
  int i = 0;
  while(yytext[i] != '\0')
  {
    if(yytext[i] == '\n')
    {
      rownum++;
      colnum = 1;
    }
    else
      colnum++;
    i++;
  }
}
"//".*"\n" {
  rownum++;
  colnum = 1;
}

"("|")"|"{"|"}" {
  tk = alloctoken();
  if(strcmp(yytext, "(") == 0)
    setTokenargs(tk, yytext, 0, rownum, colnum, LB);
  else if(strcmp(yytext, ")") == 0)
    setTokenargs(tk, yytext, 0, rownum, colnum, RB);
  else if(strcmp(yytext, "{") == 0)
    setTokenargs(tk, yytext, 0, rownum, colnum, LCB);
  else if(strcmp(yytext, "}") == 0)
    setTokenargs(tk, yytext, 0, rownum, colnum, RCB);

  colnum += 1;
  return tk;
}

\"(.)*\" {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, LITERAL);
  colnum += strlen(yytext);
  return tk;
}

\n {
  rownum++;
  colnum = 1;
}

"<" {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, LT);
  colnum += strlen(yytext);
  return tk;
}

">" {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, GT);
  colnum += strlen(yytext);
  return tk;
}

"<=" {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, LTE);
  colnum += strlen(yytext);
  return tk;
}

">=" {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, GTE);
  colnum += strlen(yytext);
  return tk;
}

"==" {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, EE);
  colnum += strlen(yytext);
  return tk;
}

"!=" {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, NE);
  colnum += strlen(yytext);
  return tk;
}

\t {
  colnum += 8;
}

"++"|"--" {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, AOP);
  colnum += strlen(yytext);
  return tk;
}

\+ {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, ADD);
  colnum += strlen(yytext);
  return tk;
}

\- {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, SUB);
  colnum += strlen(yytext);
  return tk;
}

\* {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, MUL);
  colnum += strlen(yytext);
  return tk;
}

\/ {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, DIV);
  colnum += strlen(yytext);
  return tk;
}

\% {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, MODULUS);
  colnum += strlen(yytext);
  return tk;
}

\= {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, ASSIGN);
  colnum += strlen(yytext);
  return tk;
}

[\;, \,] {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, SS);
  colnum += strlen(yytext);
  return tk;
}

"if"|"else"|"for"|"while"|"int"|"char"|"do"|"return"|"void"|"float"|"double" {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, KEYWORD);
  colnum += strlen(yytext);
  return tk;
}

[-]?[0-9]+([.]?[0-9]+)? {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, NUMBER);
  colnum += strlen(yytext);
  return tk;
}

[a-zA-Z][a-zA-Z0-9_]* {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, IDENTIFIER);
  colnum += strlen(yytext);
  return tk;
}

"&&"|"||" {
  tk = alloctoken();
  setTokenargs(tk, yytext, 0, rownum, colnum, LOP);
  colnum += strlen(yytext);
  return tk;
}

. {
  colnum++;
}

%%

int main()
{
  symbolTable* table[SIZE];
  init(table);
  char dtb[50];
  int dtbfull = 0;
  token* idbuf[50];
  int idbufcnt = 0;
  token* argbuf[50];
  int argbufcnt = 0;
  int argbufact = 0;
  int keywordprev = 0;
  int argbufsize[50];
  char rettypebuf[50];
  char argdtype[50][10];

  yyin = fopen("input.c", "r");

  int cnt = 0;
  int scope = 0;

  while(tk == yylex())
  {
    if(strcmp(tk->lexemename, "int") == 0 || strcmp(tk->lexemename, "float") == 0 || strcmp(tk->lexemename, "char") == 0 || strcmp(tk->lexemename, "double") == 0)
    {
      if(!argbufact)
        strcpy(rettypebuf, tk->lexemename);
      dtbfull = 1;
      strcpy(dtb, tk->lexemename);
    }
    else if(strcmp(tk->lexemename, ";") == 0 && dtbfull == 1)
    {
      for(int i = 0; i < idbufcnt; i++)
      {
        int size = 4;
        if(strcmp(dtb, "int") == 0)
          size = 4;
        else if(strcmp(dtb, "float") == 0)
          size = 8;
        insert(idbuf[i], size, dtb, scope, NULL, 0, NULL, table, 0);
      }
      idbufcnt = 0;
      dtbfull = 0;
    }
    else if(keywordprev == 0 && strcmp(tk->lexemename, "(") == 0)
      argbufact = 1;
    else if(strcmp(tk->lexemename, ")") == 0)
    {
      if(keywordprev == 0)
      {
        printf("%s\n", idbuf[0]->lexemename);
        for(int i = 0; i < argbufcnt; i++)
          insert(argbuf[i], argbufsize[i], argdtype[i], 1, NULL, 0, NULL, table, 1);
        insert(idbuf[0], -1, NULL, scope, argbuf, argbufcnt, rettypebuf, table, 0);
        argbufcnt = 0;
        idbufcnt = 0;
        dtbfull = 0;
      }
      argbufact = 0;
      keywordprev = 0;
    }
    else if(tk->type == IDENTIFIER)
    {
      if(dtbfull && argbufact == 0)
      {
        idbuf[idbufcnt++] = tk;
      }
      else if(argbufact)
      {
        argbuf[argbufcnt] = tk;
        int size = 4;
        if(strcmp(dtb, "int") == 0)
          size = 4;
        else if(strcmp(dtb, "float") == 0)
          size = 8;
        argbufsize[argbufcnt] = size;
        strcpy(argdtype[argbufcnt++], dtb);
      }
      else
      {
        if(strcmp(tk->lexemename, "printf") == 0 || strcmp(tk->lexemename, "scanf") == 0)
        {
          keywordprev = 1;
          continue;
        }
        tk->index = hash(tk);
      }
    }
    else if(strcmp(tk->lexemename, "for") == 0 || strcmp(tk->lexemename, "while") == 0 || strcmp(tk->lexemename, "if") == 0)
      keywordprev = 1;
    else if(strcmp(tk->lexemename, "{") == 0)
      scope++;
    else if(strcmp(tk->lexemename, "}") == 0)
      scope--;
    printf("<%d %d %d %s %s>\n", tk->index, tk->row, tk->col, tk->lexemename, tokentypestr[tk->type]);
  }
  print(table);
}

int yywrap()
{
  return 1;
}
