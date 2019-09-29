#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TableLength 30

enum tokenType
{
	EOFILE = -1,
	LESS_THAN, 
	LESS_THAN_OR_EQUAL,
	GREATER_THAN, 
	GREATER_THAN_OR_EQUAL,
	EQUAL,
	NOT_EQUAL
};

struct token
{
	char *lexeme;
	int index;
	int rowno, colno;
	enum tokenType type;
};

struct ListElement
{
	struct token tok;
	struct ListElement *next;
};

struct ListElement *TABLE[TableLength];

void Initialize()
{
	for(int i = 0; i < TableLength; i++)
	{
		TABLE[i] = NULL;
	}
}

void Display()
{

}

int HASH(char *str)
{
	// Develop an OpenHash function on a string
}

int SEARCH(char *str)
{
	
}