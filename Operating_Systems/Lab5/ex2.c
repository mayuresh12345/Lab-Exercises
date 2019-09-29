/* 
Thread Termination

pthread_join()

Two parameters: 
1) handle of the thread that is to be waited for
2) 0 or the address of a pointer to void, which will hold the value returned by the child thread

*/

#include <stdio.h>
#include <pthread.h>

void* thread_code(void* param)
{
	printf("In thread code\n");
}
int main()
{
	pthread_t thread;
	pthread_create(&thread, 0, &thread_code, 0);
	printf("In main thread\n");
	pthread_join(thread, 0);
}