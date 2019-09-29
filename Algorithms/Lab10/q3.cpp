#include <iostream>
#include <stdlib.h>
using namespace std;

int max(int a, int b)
{
	if(a > b)
		return a;
	return b;
}

int main()
{
	int n;
	cout << "Enter the number of items: ";
	cin >> n;

	cout << "Enter the knapsack capacity: ";
	int W;
	cin >> W;

	int w[n], v[n];
	int F[n+1][W+1];
	
	int i, j, k;
	for(i = 0; i <= n; i++)
	{
		for(j = 0; j <= W; j++)
			F[i][j] = -1;
	}
	for(i = 0; i <= n; i++)
		F[i][0] = 0;
	for(j = 0; j <= W; j++)
		F[0][j] = 0;
	

	cout << "Enter the weights: ";
	for(i = 0; i < n; i++)
		cin >> w[i];
	
	cout << "Enter the corresponding values: ";
	for(i = 0; i < n; i++)
		cin >> v[i];

	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= W; j++)
		{
			if(j - w[i] >= 0)
				F[i][j] = max((F[i - 1][j]), (v[i] + F[i - 1][j - w[i]]));
			else
				F[i][j] = F[i - 1][j];
		}
	}
	cout << "The answer is: " << F[n][W] << endl;

	// // MFKnapsack()
	// int value;
	// for(i = 0; i < n; i++)
	// {
	// 	for(j = 0; j < W; j++)
	// 	{
	// 		if(F[i][j] < 0)
	// 		{
	// 			if(j < w[i])
	// 				value = MFKnapsack[i - 1][j];
	// 			else
	// 				value = max(MFKnapsack[i - 1][j], v[i] + MFKnapsack[i - 1][j - w[i]])
	// 			F[i][j] = value;

	// 		}
	// 	}
	// }

}