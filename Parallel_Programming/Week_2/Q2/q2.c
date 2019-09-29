#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int rank, size, num;
	int i;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0) // master process
	{
		printf("Enter a number: ");
		scanf("%d", &num);
		for(i = 1; i < size; i++)
			MPI_Send(&num, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
		fprintf(stdout, "I have send %d from master\n", num);
		fflush(stdout);
	}
	else
	{
		MPI_Recv(&num, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		fprintf(stdout, "I have received %d in process %d\n", num, rank);
		fflush(stdout);
	}
	MPI_Finalize();
}
