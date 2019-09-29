#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	int i, j, k;
	char *str, *pattern;
	str = (char *)malloc(sizeof(char) * 100);
	pattern = (char *)malloc(sizeof(char) * 100);

	cout << "Enter the string: ";
	fgets(str, 100, stdin);
	cout << "Enter the pattern: ";
	fgets(pattern, 100, stdin);

	int n = strlen(str);
	int m = strlen(pattern);
	int opcount = 0;

	for(i = 0; i < n - m + 1; i++)
	{
		j = 0, k = 0;
		while(pattern[k] == str[i + k])
		{
			k++;
			opcount++;
			if(k == m - 1)
			{
				cout << "Found\n";
			}
		}
	}

	cout << "Opcount = " << opcount << endl;
}