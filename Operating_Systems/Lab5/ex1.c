/* 

pthread_create() - creates new thread.
Parameters: 1) ptr to pthread structure - returns handle to the thread
			2) ptr to thread attribrutes structure (NULL ptr if default attribrutes are used)
			3) address of the routine to be executed
			4) Value or pointer to be passes into the new thread as a parameter

*/
#include <pthread.h>
#include <stdio.h>

void *thread_code(void* param)
{
	printf("In thread code\n");
}
int main()
{
	pthread_t thread;
	pthread_create(&thread, 0, &thread_code, 0);
	printf("In main thread\n");
}