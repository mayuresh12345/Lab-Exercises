#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print(char *str, int row, int col)
{
	for(int i = 0; str[i] != '\0'; i++)
	{
		printf("%c", toupper(str[i]));
	}
	printf("\tRow = %d\tColumn = %d\n", row, col);
}
int main()
{
	int i, j, k;
	FILE *f1;
	f1 = fopen("input.c", "r");
	int row = 1, col = 1;
	int c;
	char kw[8][100] = {"int", "float", "break", "for", "while", "continue", "if", "else"};

	int n = sizeof(kw) / (sizeof(char) * 100);
	// printf("%d\n", n);
	
	do
	{
		c = getc(f1);
		char buf[100];
		int buf_len = 0;
		int flag = 0;
		// printf("%c", c);
		// if(isalpha(c))
		// {
		// 	buf[buf_len++] = c;
		// 	while((c = getc(f1)) != ' ')
		// 	{
		// 		buf[buf_len++] = c;
		// 		row++;
		// 	}
		// 	buf[buf_len] = '\0';
		// 	printf("%s\n", buf);
			// for(i = 0; i < n; i++)
			// {
			// 	if(strcmp(kw[i], buf) == 0)
			// 	{
			// 		flag = 1;
			// 		print(buf, row, col);
			// 	}
			// }
		// }
		while(isalpha(c))
		{
			buf[buf_len++] = c;
			col++;
			flag = 1;
			c = getc(f1);
		}
		if(flag == 1)
		{
			buf[buf_len] = '\0';
			for(i = 0; i < n; i++)
			{
				if(strcmp(kw[i], buf) == 0)
				{
					print(buf, row, col - buf_len);
				}
			}
		}
		if(c == '\n')
		{
			row++;
			col = 1;
		}
		else
			col++;
	}while(c != EOF);

}