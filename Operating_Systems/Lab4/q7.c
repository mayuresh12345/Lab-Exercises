#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
int main()
{
	char dirname[10];
	DIR* p;
	struct dirent *d;
	printf("Enter directory name\n");
	scanf("%s", dirname);
	p = opendir(dirname);
	if(p == NULL)
	{
		printf("Can't find directory");
		exit(0);
	}
	while(d = readdir(p))
		printf("%s\n", d->d_name);
	return 0;
}