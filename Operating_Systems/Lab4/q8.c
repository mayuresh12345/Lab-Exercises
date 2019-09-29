#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	pid_t pid;
	pid = fork();
	int status;
	char *argv[100] ;
	*argv = "wc q1.c";
	if(pid < 0)
	{
		fprintf(stderr, "Fork Failed");
		exit(-1);
	} 
	else if(pid == 0)
	{
		execlp("wc", "wc", "q1.c", NULL);
	}
	else
	{
		wait(&status);
		printf("Child complete\n");
		exit(0);
	}
}