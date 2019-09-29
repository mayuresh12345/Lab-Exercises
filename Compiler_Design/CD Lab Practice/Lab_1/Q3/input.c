#include <stdio.h>

int main()
{
int a;
for(a = 0; a < 100; a++)
{
	if(a == 5)
	{
		break;
	}
	else if(a > 100)
		continue;
}
}
