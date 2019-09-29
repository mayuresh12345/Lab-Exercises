#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

__global__ void CUDASubstring(char *A, char *C, int *sL, int *pFound)
{
	int id = threadIdx.x;
	if(id == 0 || A[id-1] == ' ')
	{
		int fMatch = 1;
		for (int i = 0; i < *sL; i++)
		{
			if (A[id + i] != C[i])
				fMatch = 0;
		}
		if (fMatch == 1)
		{
			atomicAdd(pFound, 1);
		}
	}
}

int main(int argc, char const *argv[])
{
	char A[N];
	char C[N];

	char *pA, *pC;
	//int *pL;

	printf("Enter string(A): ");
	scanf("%[^\n]%*c", A);

	printf("Enter substring(C): ");
	scanf("%[^\n]%*c", C);

	int L = strlen(A);
	int sL = strlen(C);
	int *pFound, *psL;
	//printf("C = \n");

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

	cudaMalloc((void**)&pA, L * sizeof(char));
	cudaMalloc((void**)&pC, sL * sizeof(char));
	cudaMalloc((void**)&psL, sizeof(int));
	cudaMalloc((void**)&pFound, sizeof(int));

	int t = 0;
	//cudaMemcpy(pA, A, L * sizeof(char), cudaMemcpyHostToDevice);
	cudaMemcpy(pA, A, L * sizeof(char), cudaMemcpyHostToDevice);
	cudaMemcpy(pC, C, sL * sizeof(char), cudaMemcpyHostToDevice);
	cudaMemcpy(psL, &sL, sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(pFound, &t, sizeof(int), cudaMemcpyHostToDevice);

	cudaError_t error = cudaGetLastError();

	if (error != cudaSuccess)
	{
		printf("CUDA Error1: %s\n", cudaGetErrorString(error));
	}

	CUDASubstring<<<1, L>>>(pA, pC, psL, pFound);

	error = cudaGetLastError();

	if (error != cudaSuccess)
	{
		printf("CUDA Error2: %s\n", cudaGetErrorString(error));
	}

	int found;

	cudaMemcpy(&found, pFound, sizeof(int), cudaMemcpyDeviceToHost);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime, start, stop);

	/*printf("Value of C in Host:\n");

	for (int i = 0; i < N; ++i)
	{
		printf("%c\n", C[i]);
	}*/

	if(found != 0)
		printf("Found %d times\n", found);
	else
		printf("Not Found\n");

	printf("Time Taken = %f\n", elapsedTime);

	cudaFree(pA);
	cudaFree(pC);

	return 0;
}
