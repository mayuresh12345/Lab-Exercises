#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
using namespace std;

int inc[50], w[50], sum, n;

int fwd(int i, int wt, int total)
{
	return (((wt+total) >= sum) && ((wt == sum) || (wt + w[i + 1] <= sum)));	
}

void sumset(int i, int wt, int total)
{
	int j;
	if(fwd(i, wt, total))
	{
		if(wt == sum)
		{
			cout << "\n{\t";
			for(j = 0; j <= i; j++)
				if(inc[j])
					cout << w[j] << "\t";
				cout << "}\n";
		}
		else
		{
			inc[i+1] = TRUE;
			sumset(i + 1, wt + w[i + 1], total - w[i + 1]);
			inc[i+1] = FALSE;
			sumset(i + 1, wt, total - w[i + 1]);
		}

	}
}
int main()
{
	int i, j, n, temp, total = 0;
	cout << "\nHow many numbers do you want to enter: ";
	cin >> n;
	cout << "\nEnter the numbers: ";
	for(i = 0; i < n; i++)
	{
		cin >> w[i];
		total += w[i];
	}
	cout << "Enter the sum: ";
	cin >> sum;
	for(i = 0; i <= n; i++)
	{
		for(j = 0; j < n - 1; j++)
		{
			if(w[j] > w[j + 1])
			{
				temp = w[j];
				w[j] = w[j+1];
				w[j + 1] = temp;
			}
		}
	}
	if(total < sum)
		cout << "Not possible\n";
	else
	{
		for(i = 0; i < n; i++)
			inc[i] = 0;
		cout << "The solution using backtracking is: \n";
		sumset(-1, 0, total);
	}
}
