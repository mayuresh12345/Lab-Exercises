#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char c, buf[10];
	FILE *fp = fopen("ex_copy.c", "r");
	c = fgetc(fp);

	if(fp == NULL)
	{
		printf("Error in opening file\n");
		exit(0);
	}
	while(c != EOF)
	{
		int i = 0;
		buf[0] = '\0';
		if(c == '=')
		{
			buf[i++] = c;
			c = fgetc(fp);
			if(c == '=')
			{
				buf[i++] = c;
				buf[i] = '\0';
				printf("\nRelational operator: %s", buf);
			}
			else
			{
				buf[i] = '\0';
				printf("\nAssignment operator: %s", buf);
			}
		}
		else
		{
			if(c == '<' || c == '>' || c == '!')
			{
				buf[i++] = c;
				c = fgetc(fp);
				if(c == '=')
				{
					buf[i++] = c;
				}
				buf[i] = '\0';
				printf("\nRelational Operator: %s", buf);
			}
			else
			{
				buf[i] = '\0';
			}
		}
		c = fgetc(fp);
	}
}