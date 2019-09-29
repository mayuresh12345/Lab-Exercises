#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main()
{
	char kw[8][100] = {"int", "float", "break", "for", "continue", "if", "else", "FILE"};
	FILE *f1;
	int c1, c2;
	f1 = fopen("q3_copy.c", "r");
	if(f1 == NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}
	int line = 1, col = 1;
	int i, j = 0, k;
	int flag;
	do
	{
		c1 = getc(f1);
		char buf[10];
		flag = j = 0;
		while(isalpha(c1))
		{
			buf[j++] = c1;
			col++;
			c1 = getc(f1);
			flag = 1;
		}
		buf[j] = '\0';
		
		if(flag == 1)
		{
			for(i = 0; i < 8; i++)
			{
				if(strcmp(buf, kw[i]) == 0)
				{
					printf("Line = %d\tCol = %d\t", line, col);
					k = 0;
					while(buf[k] != '\0')
						putchar(toupper(buf[k++]));
					putchar('\n');
				}
			}
		}
		
		if(c1 == '\n')
		{
			line++;
			col = 1;
		}
		else if(c1 == ' ')
			col++;
	}while(c1 != EOF);
	fclose(f1);
	return 0;
}
