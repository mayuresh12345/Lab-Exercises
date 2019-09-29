#include <stdio.h>

int main()
{
	int M, N, P;
	printf("Enter M, N, P: ");
	scanf("%d %d %d", &M, &N, &P);
	int a[M][N], b[N][P];
	int i, j, k;
	printf("Enter matrix a: \n");
	for(i = 0; i < M; i++)
	{
		for(j = 0; j < N; j++)
			scanf("%d", &a[i][j]);
	}
	printf("Enter matrix b: \n");
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < P; j++)
			scanf("%d", &b[i][j]);
	}

	int c[M][P];

	for(i = 0; i < M; i++)
	{
		for(j = 0; j < P; j++)
		{
			c[i][j] = 0;
			for(k = 0; k < N; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}

	for(i = 0; i < M; i++)
	{
		for(j = 0; j < P; j++)
			printf("%d", c[i][j]);
		printf("\n");
	}
}
