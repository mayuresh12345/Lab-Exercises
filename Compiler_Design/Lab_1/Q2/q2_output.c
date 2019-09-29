


#hello world
int main()
{
	char ppd[3][] = {"include", "define", "if"};
	
	FILE *fa, *fb;

	fa = fopen("q2_copy.c", "r");
	if(fa == NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}
	fb = fopen("q2_output.c", "w");

	int c1, c2;
	int i, j, k;
	do
	{
		c1 = getc(fa);
		char buf[8];
		if(c1 == '#')
		{
			fread(buf, sizeof(buf), 7, fa);
			if(strncmp(buf, "include", 7) || strncmp(buf, "define", 6) || strncmp(buf, "if", 2))
			{
				while(c1 != '\n')
					c1 = getc(fa);
				putc(c1, fb);
			}
			else
			{
				putc('#', fb);
				for(i = 0; i < strlen(buf); i++)
					putc(buf[i], fb);
			}
		}
		else
		{
			putc(c1, fb);
		}
	}while(c1 != EOF);
	fclose(fa);
	fclose(fb);
}ÿ