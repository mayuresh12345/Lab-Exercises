// Sum of numbers
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
struct arg_struct
{
	int a[100]; 
	int n;
};
void* child_thread(void *param)
{
	struct arg_struct *args = (struct arg_struct *) param;
	int sum = 0;

	for(int i = 0; i < args->n; i++)
	{
		if(args->a[i] >= 0)
			sum += args->a[i];
	}
	return (void *)sum;
}
int main()
{
	struct arg_struct *args = (struct arg_struct *) malloc(sizeof(struct arg_struct));
	printf("n = ");
	scanf("%d", &args->n);
	int i = 0;
	for(; i < args->n; i++)
	{
		scanf("%d", &args->a[i]);
	}
	int sum;
	pthread_t thread;
	pthread_create(&thread, 0, &child_thread, (void *)args);
	pthread_join(thread, (void **)&sum);
	printf("The sum is = %d\n", sum);
}