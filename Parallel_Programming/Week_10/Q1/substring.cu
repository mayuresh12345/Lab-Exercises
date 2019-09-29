#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

__global__ void CUDAStrCopy(char *str, char *sub, int *len2)
{
	int start = blockIdx.x;
	int end = start + *len2;
	for(int i = start; i < end; i++)
	{
		if(str[i] != sub[i - start])
			break;
		else if(i == end - 1)
			printf("Found at %d\n", (i - start));
	}
}

int main()
{
	char str[N];
	char sub[N];
	char *pstr, *psub;
	int *plen2;

	printf("Enter a string: ");
	scanf("%s", str);
	printf("Enter the substring: ");
	scanf("%s", sub);

	int len1 = strlen(str);
	int len2 = strlen(sub);

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);
	cudaMalloc((void**)&pstr, N * sizeof(char));
	cudaMalloc((void**)&psub, len2 * sizeof(char));
	cudaMalloc((void**)&plen2, sizeof(int));
	cudaMemcpy(pstr, str, N * sizeof(char), cudaMemcpyHostToDevice);
	cudaMemcpy(psub, sub, len2 * sizeof(char), cudaMemcpyHostToDevice);
	cudaMemcpy(plen2, &len2, sizeof(int), cudaMemcpyHostToDevice);

	CUDAStrCopy<<<N - len2, 1>>>(pstr, psub, plen2);


	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime, start, stop);
	int i;
	/*
		printf("Value of C in host after kernel execution\n");
		for(int i = 0; i < N; i++)
			printf("%c\n", C[i]);
	*/
	printf("Time taken = %f", elapsedTime);
	cudaFree(pstr);
	cudaFree(psub);
	cudaFree(plen2);
	printf("\n");

	return 0;
}
