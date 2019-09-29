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
	*argv = "./q1";
	if(pid < 0)
	{
		fprintf(stderr, "Fork Failed");
		exit(-1);
	} 
	else if(pid == 0)
	{
		// if(execvp(*argv, argv) < 0)
		// 	exit(1);
		execlp("./q1", NULL);
	}
	else
	{
		wait(&status);
		printf("Child complete");
		exit(0);
	}
}