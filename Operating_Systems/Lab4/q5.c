#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
int main()
{
	int fd;
	char str[20];
	strcpy(str, "hello");
	fd = creat("hello.txt", 777);
	write(fd, str, strlen(str));
}