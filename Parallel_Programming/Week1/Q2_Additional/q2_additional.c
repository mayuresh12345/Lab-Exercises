#include "mpi.h"
#include <stdio.h>
void check(int start, int end)
{
	int count = 0;
	for(int i = start; i <= end; i++)
	{
		count = 0;
		for(int j = 1; j <= i; j++)
		{
			if(i % j == 0)
				count++;
		}
		if(count == 2)
			printf("%d\n", i);
	}
}
int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank)
		check(0, 50);
	else
		check(51, 100);
	MPI_Finalize();
	return 0;
}
