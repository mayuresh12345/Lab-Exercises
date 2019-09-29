#include "mpi.h"
#include <stdio.h>

void ErrorHandler(int error_code)
{
	if(error_code != MPI_SUCCESS)
	{
			char str[100];
			int len, error_class;
			MPI_Error_class(error_code, &error_class);
			MPI_Error_string(error_class, str, &len);
			printf("%s%d", str, len);
			MPI_Error_string(error_class, str, &len);
			printf("Error Code : %s", str);
		}
}
int main(int argc, char* argv[])
{
	int rank, size;
	int c = 3;
	int len, error_code;
	error_code = MPI_Init(&argc, &argv);
	MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	error_code = MPI_Comm_size(c, &size);
	ErrorHandler(error_code);
	printf("No. of tasks = %d\tMy rank = %d\n", size, rank);
	ErrorHandler(error_code);
	MPI_Finalize();
	return 0;
}
