#include "mpi.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
	int rank, size;
	int sum, diff, pro, div;
	int a = 10, b = 5;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	printf("My rank is %d in total %d process\n", rank, size);
	switch(rank)
	{
		case 0:
			sum = a + b;
			printf("Sum : %d\n", sum);
			break;
		case 1:
			diff = a - b;
			printf("Difference : %d\n", diff);
			break;
		case 2:
			pro = a * b;
			printf("Product : %d\n", pro);
			break;
		case 3:
			div = a / b;
			printf("Division : %d\n", div);
			break;
	}
	MPI_Finalize();
	return 0;
}
