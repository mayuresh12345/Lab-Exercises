#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
// 5 4 100 500 200 300 600 212 417 112 426
void worst_fit(int *partitions, int *processes, int n, int m)
{
	cout << "Worst Fit\n";
	int i, j, k;
	int flag = 0;
	int max_index, max = 10000;
	for(i = 0; i < m; i++)
	{
		max = -1;
		for(j = 0; j < n; j++)
		{
			int diff = partitions[j] - processes[i];
			if(diff > max && diff >= 0)
			{
				max_index = j;
				max = diff;
				flag = 1;
			}
		}
		if(flag)
		{
			cout << processes[i] << " allocated to " << partitions[max_index] << endl;
			partitions[max_index] -= processes[i];
		}
		else
			cout << processes[i] << " has to wait\n";
		flag = 0;
	}

}
void best_fit(int *partitions, int *processes, int n, int m)
{
	cout << "Best Fit\n";
	int i, j, k;
	int flag = 0;
	int min_index, min = 10000;
	for(i = 0; i < m; i++)
	{
		min = 10000;
		for(j = 0; j < n; j++)
		{
			int diff = partitions[j] - processes[i];
			if(diff < min && diff >= 0)
			{
				min_index = j;
				min = diff;
				flag = 1;
			}
		}
		if(flag)
		{
			cout << processes[i] << " allocated to " << partitions[min_index] << endl;
			partitions[min_index] -= processes[i];
		}
		else
			cout << processes[i] << " has to wait\n";
		flag = 0;
	}

}
void first_fit(int *partitions, int *processes, int n, int m)
{
	cout << "First Fit\n";
	int i, j, k;
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(partitions[j] - processes[i] >= 0)
			{
				cout << processes[i] << " allocated to " << partitions[j] << endl;
				partitions[j] -= processes[i];
				break;
			}
			else if(j == n - 1)
				cout << processes[i] << " has to wait\n";
		}
	}
}
void reset(int *arr, int *copy, int len)
{
	for(int i = 0; i < len; i++)
		arr[i] = copy[i];
}
void input(int *arr, int len)
{
	for(int i = 0; i < len; i++)
		cin >> arr[i];
}
int main()
{
	int n, m;
	cout << "No. of partitions & no. of processes: ";
	cin >> n >> m;
	int *partitions = (int *)malloc(n * sizeof(int));
	int *processes = (int *)malloc(m * sizeof(int));

	int i, j, k;
	cout << "Enter the partitions: \n";
	input(partitions, n);
	cout << "Enter the processes: \n";
	input(processes, m);

	int *storage = (int *)malloc(n * sizeof(int));
	reset(storage, partitions, n);

	cout << endl;
	first_fit(partitions, processes, n, m);
	reset(partitions, storage, n);
	
	cout << endl;
	best_fit(partitions, processes, n, m);
	reset(partitions, storage, n);
	
	cout << endl;
	worst_fit(partitions, processes, n, m);
	reset(partitions, storage, n);
	cout << endl;
}