#include "mpi.h"
#include <stdio.h>
int fac(int c)
{
	int f = 1;
	for(int i = 1; i <= c; i++)
		f *= i;
	return f;
}
int main(int argc, char* argv[])
{
	int rank, size, N, A[10], B[10], c, i;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0)
	{
		N = size;
		printf("Enter %d values: \n", N);
		for(i = 0; i < N; i++)
			scanf("%d", &A[i]);
	}
	MPI_Scatter(A, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf("Rank = %d\t Value = %d\t Factorial = %d\n", rank, c, fac(c));
	MPI_Finalize();
}
