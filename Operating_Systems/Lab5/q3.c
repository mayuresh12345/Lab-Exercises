// Generating prime numbers

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct arg_struct
{
	int low, high;
	int a[100];
};

void* child_thread(void *param)
{
	struct arg_struct *args = (struct arg_struct*) param;
	int low = args->low;
	int high = args->high;

	int i, j, k = 0; 
	int count;

	for(i = low; i <= high; i++)
	{
		count = 0;
		for(j = 1; j <= i; j++)
		{
			if(i % j == 0)
				count++;
		}
		if(count == 2)
			
			{
				printf("%d ",i);
				args->a[k++] = i;
			}
	}
	return (void *)(args);
}

int main()
{
	struct arg_struct* args = (struct arg_struct *)malloc(sizeof(struct arg_struct));
	printf("Enter the low and high values: ");
	scanf("%d %d", &args->low, &args->high);
	int arr[100] = {0};

	pthread_t thread;
	pthread_create(&thread, 0, &child_thread, (void *) args);
	pthread_join(thread, (void **)&args);
	printf("\n");
	for(int i = 0; i < (args->high - args->low); i++)
		printf("%d ",args->a[i]);
	printf("\n");

}

