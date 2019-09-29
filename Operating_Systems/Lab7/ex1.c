// Interprocess Communication
/* 

Pipes - unidirectional flow of data
call pipe()
return fd[0], fd[1]
fd[1] - connects to the write end of the pipe
fd[0] - conncets to the read end of the pipe

int pipe(int *filedes); or int pipe(int fd[2]);
returns 0 on success
returns -1 on error

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int n;
	int fd[2];
	char buf[1025];
	char *data = "Hello... this is sample data";
	pipe(fd);
	write(fd[1], data, strlen(data));
	if((n = read(fd[0], buf, 1024)) >= 0)
	{
		buf[n] = 0;
		printf("Read %d bytes from the pipe :\"%s\"\n", n, buf);
	}
	else
		perror("read");
	exit(0);
}

