#include <iostream>
using namespace std;

void printarr(int a[], int n)
{
	for(int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}
int y = 0;
void permutate(int a[], int size, int n)
{
	if(size == 1)
	{
		printarr(a, n);
		y++;
		return;
	}
	for(int i = 0; i < size; i++)
	{
		permutate(a, size - 1, n);

		if(size % 2 == 1)
			swap(a[0], a[size - 1]);
		else
			swap(a[i], a[size - 1]);
	}
}

int main()
{
	int a[] = {1, 2, 3, 4, 5};
	int n = 5;
	permutate(a, n, n);
	cout << y << endl;
}