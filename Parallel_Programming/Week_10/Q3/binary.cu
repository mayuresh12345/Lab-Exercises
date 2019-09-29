#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 1024

__global__ void CUDABinary(char *A, int *L)
{
	int i = threadIdx.x;

	int dec = (int)A[i];
	int j = 1, rem[10] = {0};

	while(dec != 0)
	{
		rem[j++] = dec % 2;
		dec /= 2;
	}

	int bin = 0;
	while(j != 0)
	{
		bin = bin * 10 + rem[j--];
	}

	printf("%d  ", bin);
	//printf("%s\n", C[i]);
}

int main(int argc, char const *argv[])
{
	char A[N];
	//char C[N];

	char *pA;
	int *pL;

	printf("Enter string(A): ");
	scanf("%[^\n]%*c", A);

	//printf("C = \n");>>>(p

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

	cudaMalloc((void**)&pA, N * sizeof(char));
	cudaMalloc((void**)&pL, sizeof(int));
	//cudaMalloc((void**)&pC, N * sizeof(char));

	int L = strlen(A);

	cudaMemcpy(pA, A, N * sizeof(char), cudaMemcpyHostToDevice);
	cudaMemcpy(pL, &L, sizeof(int), cudaMemcpyHostToDevice);

	cudaError_t error = cudaGetLastError();

	if (error != cudaSuccess)
	{
		printf("CUDA Error1: %s\n", cudaGetErrorString(error));
	}

	printf("Binary values:\n");

	CUDABinary<<<1, L>>>(pA, pL);

	error = cudaGetLastError();

	if (error != cudaSuccess)
	{
		printf("CUDA Error2: %s\n", cudaGetErrorString(error));
	}

	cudaMemcpy(A, pA, N * sizeof(char), cudaMemcpyDeviceToHost);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime, start, stop);

	//printf("Value of C in Host:\n");

	//printf("Reversed A: %s\n", A);
	/*for (int i = 0; i < N; ++i)
	{
		printf("%c\n", C[i]);
	}*/

	printf("\nTime Taken = %f\n", elapsedTime);

	cudaFree(pA);
	cudaFree(pL);
	//cudaFree(pC);

	return 0;
}
