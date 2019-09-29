#include <iostream>
#include <stdlib.h>
using namespace std;

void copy(int *a1[], int *a2[], int n)
{
	int i, j, k;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			a1[i][j] = a2[i][j];
		}
	}
}
int main()
{
	cout << "Enter the number of vertices: ";
	int n;
	cin >> n;
	int *arr[n];
	for(int i = 0; i < n; i++)
		arr[i] = (int *)malloc(n * sizeof(int));
	cout << "Enter the matrix: ";
	int i, j, k;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			cin >> arr[i][j];
		}
	}

	// Warshall's algo
	int *temp[n];
	for(int i = 0; i < n; i++)
		temp[i] = (int *)malloc(n * sizeof(int));
	copy(temp, arr, n);
	for(k = 0; k < n; k++)
	{
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
				arr[i][j] = temp[i][j]||(temp[i][k] && temp[k, j]);
		}
		copy(temp, arr, n);
	}
	cout << "Transitive Closure: \n";
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}	

}