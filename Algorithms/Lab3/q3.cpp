#include <iostream>
#include <math.h>
using namespace std;
int conditions(int arr1[], int n1, int arr2[], int n2)
{
	for(int i = 1; i < n1; i++)
	{
		for(int j = 1; j < n2; j++)
		{
			if(arr1[i] == arr2[j])
				return 0;
		}
	}
	return 1;
}
void display(int arr[], int n)
{
	for(int i = 1; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}
int main()
{
	int i, j, k;

	int n;
	cout << "How many elements: ";
	cin >> n;

	int *set = (int *)malloc(sizeof(int));

	for(i = 0; i < n; i++)
		cin >> set[i];

	cout << "Enter the sum: ";
	int sum;
	cin >> sum;
	// Generating subsets
	int size = pow(2, n);
	int storage[size][n];
	int *sumset = (int *)calloc(size, sizeof(int));
	int temp;
	int index;
	j = 0;
	int y = 0;
	for(i = 0; i < pow(2, n); i++)
	{
		temp = i;
		index = 0;
		k = 0;
		while(temp)
		{
			if(temp & 0x1)
			{
				cout << set[index] << " ";
				sumset[j] += set[index];
			}
			index++;
			temp = temp >> 1;
		}
		cout << "Sum: " << sumset[j] << endl;

		if(sum == sumset[j++])
		{
			temp = i;
			index = 0;
			int ele = 1;
			while(temp)
			{
				if(temp & 0x1)
				{
					storage[y][ele++] = set[index];
				}
				index++;
				temp = temp >> 1;
			}
			storage[y][0] = ele; // storing the first element of each set as the number of elements in the subset
			y++;
		}		
	}

	// for(i = 0; i < y; i++)
	// {
	// 	int len = storage[i][0];
	// 	cout << len <<"\t";
	// 	for(j = 1; j < len; j++)
	// 	{
	// 		cout << storage[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	cout << endl << endl << "Subsets satisfying the conditions: \n";
	for(i = 0; i < y; i++)
	{
		for(j = 0; j < y; j++)
		{
			int flag = conditions(storage[i], storage[i][0], storage[j], storage[j][0]);
			// cout << flag << endl;
			if(flag)
			{
				display(storage[i], storage[i][0]);
				display(storage[j], storage[j][0]);
			}
		}
	}
}