#include <stdio.h>
#include <stdlib.h>
#define N 3
#define M 2

__global__ void add(int *A, int *B, int *C)
{
//    int bid = blockIdx.x;
    int tid = threadIdx.x;
    
    printf("(%d)", tid);
    C[tid] = A[tid] + B[tid];    
}

int main()
{
//	int *a, *b, *c;
	int a[M * N], b[M * N], c[M * N];

	// host copies of variables a, b & c
	int *d_a, *d_b, *d_c;

	// device copies of variables a, b & c
	int size = sizeof(int) * M * N;

//	a = (int *)malloc(sizeof(int) * N);
//	b = (int *)malloc(sizeof(int) * N);
//	c = (int *)malloc(sizeof(int) * N);

	// Allocate space for device copies a, b & c
	cudaMalloc((void**)&d_a, size);
	cudaMalloc((void**)&d_b, size);
	cudaMalloc((void**)&d_c, size);
  
  int t = 1;
	// Setup input values
	printf("Enter values for a: ");
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
      a[i * N + j] = t++;
  
  t = 1;
	printf("Enter values for b: ");
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
      b[i * N + j] = t++;

	// Copy inputs to device
	cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);

	// Launch add() kernel on GPU
	add<<<1, M*N>>>(d_a, d_b, d_c);

	// Copy result back to host
	cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);

	// print result
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < N; j++)
			{
          printf("%d + %d = %d\n", a[i * N + j], b[i * N + j], c[i * N + j]);
      }
      
	}

	// Cleanup
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}