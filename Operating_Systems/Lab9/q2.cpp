#include <iostream>
#include <stdlib.h>
using namespace std;
void display(int *arr[], int n, int m)
{
	for(int i = 0; i < n; i++)
	{
		cout << "Process " << i << ": ";
		for(int j = 0; j < m; j++)
			cout << arr[i][j];
	}
	cout << endl;
}
void input(int *arr[], int n, int m)
{
	for(int i = 0; i < n; i++)
	{
		cout << "Process " << i << ": ";
		for(int j = 0; j < m; j++)
			cin >> arr[i][j];
	}
}
int main()
{
	int i, j, k;
	int n, m;
	cout << "Enter the number of Processes and Resources: ";
	cin >> n >> m;
	int *total = (int *)malloc(m * sizeof(int));
	int *available = (int *)malloc(m * sizeof(int));
	int *allocation[n], *request[n];
	for(i = 0; i < n; i++)
	{
		allocation[i] = (int *)malloc(m * sizeof(int));
		request[i] = (int *)malloc(m * sizeof(int));
	}

	 cout << "Enter the total number of resources: \n";
	for(i = 0; i < m; i++)
	{
		cin >> total[i];
		available[i] = total[i];
	}
	cout << "Enter the allocation: " << endl;
	input(allocation, n, m);
	
	cout << "Enter the request: \n";
	input(request, n, m);

	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			available[i] -= allocation[j][i];
		}
	}

	int work[m], finish[n];
	int flag;
	for(i = 0; i < m; i++)
		work[i] = available[i];

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			if(allocation[i][j] != 0)
			{
				finish[i] = 0;
				break;
			}
			finish[i] = 1;
		}
	}
	int count = 0;
	while(count < n)
	{
		for(i = 0; i < n; i++)
		{
			if(finish[i] == 0)
			{
				for(j = 0; j < m; j++)
					if(request[i][j] > work[j])
						break;
				if(j == m)
				{
					for(k = 0; k < n; k++)
						work[k] += allocation[i][k];
					finish[i] = 1;
					count++;
				}
			}
		}
	}
	flag = 1;
	for(i = 0; i < n; i++)
		if(!finish[i])
		{
			flag = 0;
		}
	if(flag)
		cout << "Not a Deadlock\n";
	else
		cout << "Deadlock\n";

	

}