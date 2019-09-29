#include <string.h>
#define SIZE 100
char* Tokentypestr[24]={"EOFFile","AOP","LB","RB","LCB","RCB","IDENTIFIER","KEYWORD","NUMBER","LOP","SS","LITERAL","LT","GT","LTE","GTE","EE","NE","ADD","SUB","MUL","DIV","MODULUS","ASSIGN"};

enum Tokentype{EOFFile=0,AOP,LB,RB,LCB,RCB,IDENTIFIER,KEYWORD,NUMBER,LOP,SS,LITERAL,LT,GT,LTE,GTE,EE,NE,ADD,SUB,MUL,DIV,MODULUS,ASSIGN};

typedef struct t
{
	char* lexemename;
	int index;
	int row,col;
	enum Tokentype type;
}token;

typedef struct symboltablentry
{
	char name[50];
	char type[50];
	int size;
	char scope;
	char* args[50];
	int argssize;
	char returntype[50];
	struct symboltableentry* next;
} smt;




void init(smt* table[])
{
	for(int i=0;i<SIZE;i++)
		table[i]=NULL;
}

int hash(token* tk)
{
	int hashValue=0;
	for(int i=1;i<=strlen(tk->lexemename);i++)
	{
		hashValue+=i*(int)tk->lexemename[i-1]; //weighted ascii
	}

	return hashValue%SIZE;
}
int search(token* tk,smt* table[])
{
	int hashValue = hash(tk);
	smt* temp=table[hashValue];
	while(temp && temp->name!=tk->lexemename)
	{
		temp = temp->next;
	}
	if(temp==NULL)
		return -1;
	else return hashValue;
}

void print(smt* table[])
{
	int i=0;
	
	printf("Name\tType\tSize\tScope\tReturnType\tArgs\n");
	for(int i=0;i<SIZE;i++)
	{
		smt* temp=table[i];
		if(temp!=NULL)
		{
			while(temp)
			{
				
				printf("%s\t%s\t%d\t%c\t%s\t\t",temp->name,temp->type,temp->size,temp->scope,temp->returntype);
				for(int i=0;i<temp->argssize;i++)
				{
					printf("%s ",temp->args[i] );
				}
				printf("\n");
				temp=temp->next;
			}
			printf("\n");

		}
	}
}
int insert(token* tk,int size, char datatype[] ,int scope , token* args[],int argumentbuffersize,char returntype[],smt* table[],int overideenter)
{
	int hashkey=search(tk,table);

	if(search(tk,table)==-1||overideenter)
	{
		int hashkey=hash(tk);
		
		smt* temp=table[hashkey];
		smt* head=table[hashkey];
		smt* newnode=(smt*)malloc(sizeof(smt));
		strcpy(newnode->name,tk->lexemename);
		if(datatype)
		strcpy(newnode->type,datatype);	
		
		newnode->size=size;

		if(returntype)
		{
			
		strcpy(newnode->returntype,returntype);
		}
		newnode->argssize=0;
		if(argumentbuffersize>0)
		{
			for(int i=0;i<argumentbuffersize;i++)
			{
				newnode->args[i]=malloc(50);
				strcpy(newnode->args[i],args[i]->lexemename);
			}
			newnode->argssize=argumentbuffersize;
		}
		if(returntype==NULL)
		{
		if(scope>0)
		{
			newnode->scope='L';
		}else
		{
			newnode->scope='G';
		}
		}
		newnode->next=NULL;

		if(table[hashkey]==NULL)
		{
			
			table[hashkey]=newnode;
		}else
		{

			while( temp->next!=NULL)
			{
				temp=temp->next;
			}
			temp->next=newnode;
			table[hashkey]=head;
		}
		return hashkey;
	}
	return hashkey;

}

