#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int rank, size, x;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank == 0)
	{
		scanf("%d", &x);
		MPI_Ssend(&x, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Recv(&x, 1, MPI_INT, size - 1, 1, MPI_COMM_WORLD, &status);
	}
	else if(rank < size - 1)
	{
		MPI_Recv(&x, 1, MPI_INT, rank - 1, )
	}
}
