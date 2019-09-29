#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
	int i, j, k;
	// ------------------- Data Structures and initialisation
	cout << "Enter the number of processes and resource types: ";
	int n, m;
	cin >> n >> m;

	int available[m], max[n][m], allocation[n][m], need[n][m], total[m];
	cout << "Enter the total instances of resources: ";
	for(i = 0; i < m; i++)
	{
		cin >> total[i];
		available[i] = total[i];
	}

	cout << "Enter the max resources that can be allocated for: ";
	for(i = 0; i < n; i++)
	{
		cout << "\nProcess " << i << ": ";
		for(j = 0; j < m; j++)
		{
			cin >> max[i][j];

		}
	}
	cout << "Enter the current allocation for: ";
	for(i = 0; i < n; i++)
	{
		cout << "\nProcess " << i << ": ";
		for(j = 0; j < m; j++)
		{
			cin >> allocation[i][j];
			need[i][j] = max[i][j] - allocation[i][j];		
		}
	}

	cout << "Available Matrix: \n";
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
			available[i] -= allocation[j][i];
		cout << available[i] << " ";
	}
	
	cout << "\nNeed Matrix\n";
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
			cout << need[i][j] << " ";
		cout << endl;
	}

	// ------------- Safety Algorithm
	int work[m], finish[n];
	
	for(i = 0; i < m; i++)
		work[i] = available[i];
	for(i = 0; i < n; i++)
		finish[i] = 0; // 0 = false

	int count = 0;

	while(count < n)
	{
		for(i = 0; i < n; i++)
		{
			if(finish[i] == 0)
			{
				for(j = 0; j < m; j++)
					if(need[i][j] > work[j])
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
	int flag = 1;
	for(i = 0; i < n; i++)
		if(!finish[i])
		{
			flag = 0;
		}
	if(flag)
		cout << "Safe State\n";
	else
		cout << "Not a Safe State\n";

}