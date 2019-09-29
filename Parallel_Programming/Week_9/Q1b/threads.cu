#include <stdio.h>
#define N 5
__global__ void add(int *a, int *b, int *c)
{
	int tid = threadIdx.x;

//	if(tid < N)
		c[tid] = a[tid] + b[tid];
}

int main()
{
//	int *a, *b, *c;
	int a[N], b[N], c[N];

	// host copies of variables a, b & c
	int *d_a, *d_b, *d_c;

	// device copies of variables a, b & c
	int size = sizeof(int) * N;

//	a = (int *)malloc(sizeof(int) * N);
//	b = (int *)malloc(sizeof(int) * N);
//	c = (int *)malloc(sizeof(int) * N);

	// Allocate space for device copies a, b & c
	cudaMalloc((void**)&d_a, size);
	cudaMalloc((void**)&d_b, size);
	cudaMalloc((void**)&d_c, size);

	// Setup input values
	printf("Enter values for a: ");
	for(int i = 0; i < N; i++)
		scanf("%d", &a[i]);
	printf("Enter values for b: ");
		for(int i = 0; i < N; i++)
			scanf("%d", &b[i]);

	// Copy inputs to device
	cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);

	// Launch add() kernel on GPU
	add<<<1, N>>>(d_a, d_b, d_c);

	// Copy result back to host
	cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);

	// print result
	for(int i = 0; i < N; i++)
		printf("%d + %d = %d\n", a[i], b[i], c[i]);

	// Cleanup
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}
