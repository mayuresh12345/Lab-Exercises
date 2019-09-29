#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fa, *fb;
	int c1, c2;
	fa = fopen("q1_copy.c", "r");
	if(fa == NULL)
	{
		printf("Cannot open		file\n");
		exit(0);
	}
	fb = fopen("q1_output.c", "w");
	do
	{
		c1 = getc(fa);
		if(c1 == ' ')
		{
			putc(c1, fb);

			c2 = getc(fa);
			
			if(c2 == '\t')
				continue;

			while(c2 == ' ')
				c2 = getc(fa);
			
			putc(c2, fb);
		}
		else if(c1 == '\t')
		{
				while(c1 == '\t')
					c1 = getc(fa);
				putc(' ', fb);
				putc(c1, fb);
		}	
		else
			putc(c1, fb);
	}while(c1 != EOF);
	fclose(fa);
	fclose(fb);
}