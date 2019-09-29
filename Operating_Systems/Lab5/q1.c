#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
void* child_thread(void* param)
{
	int n = *((int *)param);
	printf("%d\n", n);
	int i = 0, j = 1, k = 0, fib = 0;
	int *a = (int *)malloc((n - 1) * sizeof(int));
	for(k = 0; k < n; k++)
	{
		fib = i + j;
		a[k] = j;
		i = j;
		j = fib;
	}
	return (void *)a;
}
int main()
{
	int n;
	printf("How many fib numbers: ");
	scanf("%d", &n);
	pthread_t thread;
	int *a = (int *)malloc((n - 1) * sizeof(int));
	pthread_create(&thread, 0, &child_thread, (void*)&n);
	pthread_join(thread, (void **)&a);
	for(int i = 0; i < n; i++)
		printf("%d\t", a[i]);
	printf("\n");
}