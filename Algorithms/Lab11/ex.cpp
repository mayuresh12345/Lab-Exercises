#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int	a[50][50], t[50][50], root[50], parent[50], n, i, j, value, e = 0, k = 0;
int ivalue, jvalue, cost = 0, mincost = 0, TV[50], count = 0, present = 0;

void read_cost()
{
	cout << "Enter the number of vertices: ";
	cin >> n;
	cout << "Enter the cost adjacency matrix\n";
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <=n; j++)
		{
			if(i < j)
			{
				cout << i << " " << j << " = ";
				cin >> a[i][j];
				if(a[i][j] != 0)
					e++;
			}
			else if(i > j)
				a[i][j] = a[j][i];
			else
				a[i][j] = 0;
		}
	}
}
void display()
{
	if(k == n - 1)
	{
		printf("Minimum cost spanning tree is: \n");
		for(i = 1; i <= n; i++)
		{	
			for(j = 1; j <= n; j++)
			{
				if(t[i][j] != 0)
					printf("\n(%d, %d): %d", i, j, t[i][j]);
				mincost += mincost[i][j];
			}
			cout << "\nMin cost of spanning Tree = " << mincost << endl;
		}
		else
			cout << "The graph is not connected\n";
	}
}
int check_reach(int v)
{
	int p;
	for(p = 1; p <= count; p++)
		if(TV[p] == v)
			return 1;
		return 0;
}
void prims()
{
	while(e && k < n - 1)
	{
		for(i = 1; i <= n; i++)
		{
			for(j = 1; j <= n; j++)
			{
				if(a[i][j] != 0)
				{
					int x, y;
					x = check_reach(i);
					y = check_reach(j);
					if((x == 1) && (y == 0))
					{
						present = 1;
						if(a[i][j] < cost || cost = 0)
						{
							cost = a[i][j];
							ivalue = i;
							jvalue = j;
						}
						if(present == 0)
							break;
						a[ivalue][jvalue] = 0;
						a[jvalue][ivalue] = 0;
						e--;
						TV[++count] = jvalue;
						t[ivalue][jvalue] = cost;
						k++;
						present = cost = 0;
					}
				}
			}
		}
	}
}
int main()
{
	printf("\n\t\t\t PRIMS ALGO\n");
	TV[++count] = 1;
	read_cost();
	prims();
	display();
}
