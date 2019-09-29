#include <iostream>
using namespace std;

void bubblesort(int *a, int n)
{
	int i, j;
	int opcount = 0;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n - i - 1; j++)
		{
			opcount++;
			if(a[j] > a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	cout << "Opcount: " << opcount << endl;
}
int main()
{
	int i;
	cout << "No. of elements: ";
	int n;
	cin >> n;
	int *a = (int *)malloc(n * sizeof(int));
	for(i = 0; i < n; i++)
		cin >> *(a + i);
	 bubblesort(a, n);

	 for(i = 0; i < n; i++)
		cout << *(a + i) << " ";
	cout << endl;
}