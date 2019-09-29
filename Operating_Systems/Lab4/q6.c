#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
int main()
{
	int f, f1;
	char str[100];
	f = open("test.txt", O_RDONLY);
	int l = read(f, str, sizeof(str));
	f1 = creat("test1.txt", 777);
	write(f1, str, l);
}