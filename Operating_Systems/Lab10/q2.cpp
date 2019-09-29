#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
int main()
{
	int page_size, pages;
	cout << "Enter the page size and number of pages: ";
	cin >> page_size >> pages;
	int total_memory = page_size * pages;
	cout << "Total Memory: " << total_memory << endl;
	int bits = (log(total_memory)/log(2)) + 1;
	cout << "Bits: " << bits << endl;
	cout << "Enter an address to read: ";
	int addr;
	cin >> addr;
	cout << "Page number: " << addr/page_size << endl;
	cout << "Offset: " << addr%page_size << endl;

}