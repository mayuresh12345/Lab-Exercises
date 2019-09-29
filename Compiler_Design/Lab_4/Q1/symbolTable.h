#include <string.h>
#define SIZE 100
char *tokentypestr[24] = {"EOFile","AOP","LB","RB","LCB","RCB","IDENTIFIER","KEYWORD","NUMBER","LOP","SS","LITERAL","LT","GT","LTE","GTE","EE","NE","ADD","SUB","MUL","DIV","MODULUS","ASSIGN"};

enum tokentype {EOFile=0,AOP,LB,RB,LCB,RCB,IDENTIFIER,KEYWORD,NUMBER,LOP,SS,LITERAL,LT,GT,LTE,GTE,EE,NE,ADD,SUB,MUL,DIV,MODULUS,ASSIGN};

typedef struct token
{
  char lexemename[100];
  int index;
  int row, col;
  enum tokentype type;
}token;

typedef struct symbolTable
{
  char name[50];
  char type[50];
  int size;
  char scope;
  char *args[50];
  int argsize;
  char returntype[50];
  struct symbolTable* next;
}symbolTable;

void init(symbolTable* table[])
{
  for(int i = 0; i < SIZE; i++)
    table[i] = NULL;
}

int hash(token* tk)
{
  int hashValue = 0;
  for(int i = 1; i <= strlen(tk->lexemename); i++)
    hashValue += i * (int)(tk->lexemename[i - 1]);

  hashValue %= SIZE;
  return hashValue;
}

int search(token *tk, symbolTable* table[])
{
  int hashValue = hash(tk);
  symbolTable* temp = table[hashValue];
  while(temp && temp -> name != tk->lexemename)
    temp = temp->next;
  if(temp == NULL)
    return -1;
  else return hashValue;
}

void print(symbolTable* table[])
{
  int i = 0;
  printf("Name\tType\tSize\tScope\tReturn Type\tArgs\n");

  for(i = 0; i < SIZE; i++)
  {
    symbolTable* temp = table[i];
    if(temp != NULL)
    {
      while(temp)
      {
          printf("%s\t%s\t%d\t%c\t%s\t\t", temp->name, temp->type, temp->size, temp->scope, temp->returntype);
          for(int j = 0; j < temp->argsize; j++)
            printf("%s ", temp->args[i]);
          printf("\n");
          temp = temp->next;
      }
      printf("\n");
    }
  }
}

int insert(token* tk, int size, char datatype[], int scope, token* args[], int argsize, char returntype[], symbolTable* table[], int id)
{
  int hashkey = search(tk, table);

  if(search(tk, table) == -1 || id)
  {
    int hashkey = hash(tk);
    symbolTable* temp = table[hashkey];
    symbolTable* head = table[hashkey];
    symbolTable* newnode = (symbolTable*) malloc(sizeof(symbolTable));

    strcpy(newnode->name, tk->lexemename);
    if(datatype)
      strcpy(newnode->type, datatype);
    newnode->size = size;

    if(returntype)
      strcpy(newnode->returntype, returntype);
    newnode->argsize = 0;

    if(argsize > 0)
    {
      for(int i = 0; i < argsize; i++)
      {
        newnode->args[i] = (char *)malloc(sizeof(char) * 50);
        strcpy(newnode->args[i], args[i]->lexemename);
      }
      newnode->argsize = argsize;
    }
    if(returntype == NULL)
    {
      if(scope > 0)
        newnode->scope = 'L';
      else
        newnode->scope = 'G';
    }
    newnode->next = NULL;
    if(table[hashkey] == NULL)
      table[hashkey] = newnode;
    else
    {
      while(temp->next != NULL)
        temp = temp->next;
      temp->next = newnode;
      table[hashkey] = head;
    }
    return hashkey;
  }
  return hashkey;
}
