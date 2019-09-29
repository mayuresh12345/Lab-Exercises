#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	pid_t pid;
	pid = fork();
	if(pid == -1)
		printf("ERROR child not created\n");
	else if(pid == 0)
	{
		printf("In Child\n");
		printf("Child process ID = %d\n", getpid());
		printf("Parent process ID = %d\n",getppid());
		exit(0);
	}
	else
	{
		wait(NULL);
		printf("Parent\n");
		printf("Child process ID = %d\n", getpid());
		printf("Parent process ID = %d\n",getppid());
	}

}