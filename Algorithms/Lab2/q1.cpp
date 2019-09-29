#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	int m, n;
	cout << "Enter the two numbers: ";
	cin >> m >> n;

	int min = fmin(m, n);

	int opcount = 0;

	while(min > 0)
	{
		opcount++;
		if(m%min == 0 && n%min == 0)
			break;
		min--;
	}

	cout << "Opcount = " << opcount << endl;
	cout << "GCD = " << min << endl;
}