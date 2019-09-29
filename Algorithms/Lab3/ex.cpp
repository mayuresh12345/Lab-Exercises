#include <iostream>
using namespace std;

void selectionsort(int *a, int n)
{
	int i, j, min;
	int temp;
	int opcount = 0;
	for(i = 0; i < n - 1; i++)
	{
		min = i;
		for(j = i + 1; j < n; j++)
		{
			++opcount;
			if(a[j] < a[min])
				min = j;
		}
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
	cout << "Opcount = " << opcount << endl;
}
int main()
{
	int *a, i;
	int n = 5;
	a = (int *)malloc(n * sizeof(int));
	for(i = 0; i < n; i++)
		cin >> *(a+i);
	selectionsort(a, n);
	for(i = 0; i < n; i++)
		cout << *(a + i) << " ";
	cout << endl;
}