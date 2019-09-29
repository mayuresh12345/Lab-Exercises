#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
int place(int x[], int k)
{
	int i;
	for(i = 1; i < k; i++)
		if(x[i] == x[k] || (abs(x[i] - x[k])) == abs(i-k))
			return 0;
	return 1;
}
void printsolution(int n, int x[])
{
	int i, j;
	char c[10][10];
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
			c[i][j] = 'X';
	}
	for(i = 1; i <= n; i++)
		c[i][x[i]] = 'Q';
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
			cout << c[i][j] << "\t";
		cout << endl;
	}
}
void nqueens(int n)
{
	int x[10], count = 0, k = 1;
	x[k] = 0;
	while(k != 0)
	{
		x[k] += 1;
		while(x[k] <= n && (!place(x, k)))
			x[k] += 1;
		if(x[k] <= n)
		{
			if(k == n)
			{
				count ++;
				cout <<"\nSolution: " << count << endl;
				printsolution(n, x);
			}
			else
			{
				k++;
				x[k] = 0;
			}
		}
		else
			k--;
	}
}
int main()
{
	int n;
	cout << "Enter the number of queens: ";
	cin >> n;
	nqueens(n);
}