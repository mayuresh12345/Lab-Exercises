#include <stdio.h>
int main()
{
	int c = 0;
	READ("%d", &c);
	WRITE("%d", c);
}