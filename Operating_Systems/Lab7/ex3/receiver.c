/*

Message Queues

Creation - msgget(); two parameters: 1) queue ket	2) flags
IPC_PRIVATE - used to create a private message queue

#include <sys/msg.h>

int msgctl(int msqid, int cmd, struct msqid_ds *buf);
int msgget(key_t key, int msgflg); -- returns +ve number on success; -1 on failure
int msgrcv(int msqid, void* msg_ptr, size_t msg_sz, long int msgtype, int msgflg);
int msgsnd(int msqid, const void *msg+ptr, size_t msg_sz, int msgflg);


struct my_message
{
	long int message_type;
	// The data you wish to transfer
};

*/

// Receiver Program

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msg_st
{
	long int my_msg_type;
	char some_text[BUFSIZ];
};

int main()
{
	int running = 1;
	int msgid;
	struct my_msg_st some_data;
	long int msg_to_recieve = 0;
	msgid = msgget((key_t)1234, 0666|IPC_CREAT);
	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	while(running)
	{
		if(msgrcv(msgid, (void *)&some_data, BUFSIZ, msg_to_recieve, 0) == -1)
		{
			fprintf(stderr, "msgget failed with error: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		printf("You wrote: %s", some_data.some_text);
		if(strncmp(some_data.some_text, "end", 3) == 0)
			running = 0;
	}
	if(msgctl(msgid, IPC_RMID, 0) == -1)
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
