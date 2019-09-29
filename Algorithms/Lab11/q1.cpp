#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

int i, j, k, a, b, u, v, n, ne = 1;
int minv, mincost = 0, cost[9][9], parent[9];
int find(int i)
{
	while(parent[i])
		i = parent[i];
	return i;
}
int uni(int i, int j)
{
	if(i != j)
	{
		parent[j] = i;
		return i;
	}
	return 0;
}

int main()
{
	cout << "Enter the no. of vertices: ";
	cin >> n;
	cout << "Enter the cost adjacency matrix: ";
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			printf("(%d, %d) = ", i, j);
			cin >> cost[i][j];
			if(cost[i][j] == 0)
				cost[i][j] = 999;
		}
	}
	cout << "The edges of Minimum Cost Spanning Tree are: \n";
	while(ne < n)
	{
		for(i = 1, minv = 999; i <= n; i++)
		{
			for(j = 1; j <= n; j++)
			{
				if(cost[i][j] < minv)
				{
					minv = cost[i][j];
					a = u = i;
					b = v = j;
				}
			}
		}
		u = find(u);
		v = find(v);
		if(uni(u, v))
		{
			printf("%d edge (%d, %d) = %d\n", ne++, a, b, minv);
			mincost += minv;
		}
		cost[a][b] = cost[b][a] = 999;
	}
	cout << "Minimum cost = " << mincost << endl;

}