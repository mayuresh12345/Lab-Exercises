#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int arr[4][4];
	if(rank == 0)
	{
		printf("Enter Matrix: \n");
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
				scanf("%d", &arr[i][j]);
	}
	int s1[4], s2[4];
	MPI_Scatter(arr, 4, MPI_INT, s1, 4, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scan(s1, s2, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	printf("Rank = %d\t", rank);
	for(int i = 0; i < 4; i++)
		printf("%d ", s2[i]);
	printf("\n");
}
