#include "mpi.h"
#include <stdio.h>
int main(int argc, char* argv[])
{
	int rank, size, done = 0, n, numProcs, i, rc;
	double pi25dt = 3.141592653589793238462643;
	double mypi, pi, h, sum, x, a;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	while(!done)
	{
		if(rank == 0)
		{
			printf("Enter the no. of intervals: ");
			scanf("%d", &n);
		}
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		if(n == 0)
			break;
		h = 1.0 / (double)n;
		sum = 0.0;
		for(i = rank + 1; i <= n; i += size)
		{
			x = -h * ((double)i - 0.5);
			sum += 4.0 / (1.0 + x * x);
		}
		mypi = h * sum;
		MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		if(rank == 0)
		{
			printf("Pi is approximately %.16f, Error is %.16f\n", pi, fabs(pi - pi25dt));
		}
	}
	MPI_Finalize();
}
