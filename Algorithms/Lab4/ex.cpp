#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int Knapsack(int *w, int *v, int n, int B)
{
	int i, temp;
	int maxVal = 0, maxSequence = 0;
	int totalWeight, totalValue;
	int opcount = 0;
	int index = 0;
	for(i = 0; i < pow(2, n); i++)
	{
		opcount++;
		temp = i;
		totalWeight = totalValue = 0;
		index = 0;
		while(temp)
		{
			if(temp & 0x1)
			{
				totalWeight += w[index];
				totalValue += v[index];
			}
			index++;
			temp >>= 1;
		}
		if(totalWeight <= B && totalValue > maxVal)
		{
			maxVal = totalValue;
			maxSequence = i;
			cout << i << endl;
		}
	}
	cout << "\nOperation Count = " << opcount << endl;
	return maxSequence;
}

int main(int argc, char const *argv[])
{
	int *v, *w, n, knaps, B;
	cout << "Enter the number of elements: ";
	cin >> n;
	v = (int *)calloc(n, sizeof(int));
	w = (int *)calloc(n, sizeof(int));
	cout << "Enter the weights: ";
	for (int i = 0; i < n; ++i)
	{
		cin >> w[i];
	}
	cout << "Enter the values: ";
	for (int i = 0; i < n; ++i)
	{
		cin >> v[i];
	}
	cout << "Please enter the knapsack capacity: ";
	cin >> B;
	knaps = Knapsack(w, v, n, B);
	cout << "Knapsack contains the following items\n";
	int i = 0;
	while(knaps)
	{
		if(knaps & 0x1)
			cout << "Item " << (i+1) << "\tValue " << v[i];
		i++;
		knaps >>= 1;
	}
	return 0;
}












