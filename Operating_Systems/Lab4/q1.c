#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int status;
	pid_t pid;
	pid = fork();
	if(pid == -1)
		printf("Error child not created\n");
	else if(pid == 0)
	{
		printf("Im the child\n");
		exit(0);
	}

	else
	{
		wait(&status);
		printf("\nI'm the parent!");
		printf("\n child returned: %d\n", status);
	}

}