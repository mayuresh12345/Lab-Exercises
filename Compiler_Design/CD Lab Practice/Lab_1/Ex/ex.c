#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *f1, *f2;
	f1 = fopen("input.c", "r");
	if(!f1)
	{
		printf("File not opened\n");
		exit(0);
	}
	f2 = fopen("output.c", "w");
	int c = getc(f1);
	while(c != EOF)
	{
		if(c == '/')
		{
			c = getc(f1);
			if(c == '/')
			{
				while(c != '\n')
					c = getc(f1);
			}
			else if(c == '*')
			{
				c = getc(f1);
				while(1)
				{
					c = getc(f1);
					if(c == '*')
					{
						c = getc(f1);
						if(c == '/')
							break;
					}
				}
			}
		}
		else
			putc(c, f2);
		c = getc(f1);

	}
}