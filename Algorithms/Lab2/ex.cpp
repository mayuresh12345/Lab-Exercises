#include <iostream>
#include <stdlib.h>
using namespace std;

int EuclidGCD(int m, int n)
{
	int r;
	int opcount = 0;
	while(n != 0)
	{
		opcount++;
		r = m % n;
		m = n;
		n = r;
	}
	cout << "opcount = " << opcount << endl;
	return m;
}

int main()
{
	int m, n;
	cout << "Enter two numbers: ";
	cin >> n >> m;
	cout << "GCD = " << EuclidGCD(m, n) << endl;
}