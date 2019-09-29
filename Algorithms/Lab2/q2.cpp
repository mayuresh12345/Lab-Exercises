#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	cout << "Enter two numbers: ";
	int m, n;
	cin >> m >> n;
	int i, j, k;
	int opcount = 0;
	int hcf = 1;
	for(i = 2; i <= fmin(m, n); i++)
	{
		opcount++;
		if(m%i == 0 && n%i == 0)
		{
			m /= i;
			n /= i;
			hcf *= i;
			i--;
		}
	}
	cout << "HCF = " << hcf << endl;
	cout << "Opcount = " << opcount << endl;
}