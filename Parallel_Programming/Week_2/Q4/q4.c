#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int rank, size;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int *buffer = (int *)malloc(sizeof(int) * 100);
	MPI_Buffer_attach(buffer, 100);

	int *arr = (int *) malloc(sizeof(int) * (size + 1));

	if(rank == 0)
	{
		printf("Enter the elements of the array: \n");
		for(int i = 1; i < (size); i++)
		{
			scanf("%d", (arr + i));
		}
		for(int i = 1; i < (size); i++)
			MPI_Bsend(&arr[i], 1, MPI_INT, i, 1, MPI_COMM_WORLD);
	}
	else if(rank%2 == 0 && rank != 0)
	{
		int ele;
		MPI_Recv(&ele, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		printf("Slave %d: ans = %d\n", rank, (ele * ele));
	}
	else
	{
		int ele;
		MPI_Recv(&ele, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		printf("Slave %d: ans = %d\n", rank, (ele * ele * ele));
	}
	MPI_Buffer_detach(buffer, 100);
	MPI_Finalize();
}
