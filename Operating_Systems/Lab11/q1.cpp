#include <iostream>
#include <stdlib.h>
#define CAPACITY 3
using namespace std;
// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
int front = 0, rear = 0;
int faults = 0, hits = 0;

int check(int frame[CAPACITY], int ref[], int n, int x)
{
	int counter[CAPACITY] = {0, 0, 0};
	int i, j, k;
	for(i = 0; i < CAPACITY; i++)
	{
		for(j = x + 1; j < n; j++)
		{
			if(frame[i] != ref[j])
				counter[i]++;
			else
				break;
		}
		// cout << "Counter [" << i << "] = " << counter[i] << endl;
	}
	int max = counter[0];
	int max_index = 0;
	for(i = 0; i < CAPACITY; i++)
	{
		if(max < counter[i])
		{
			max = counter[i];
			max_index = i;
			// cout << max_index << " ";
		}
	}

	return max_index;

}
void init_frame(int frame[CAPACITY])
{
	for(int i = 0; i < CAPACITY; i++)
		frame[i] = -1;
}
int empty(int frame[CAPACITY])
{
	int flag = 0;
	for(int i = 0; i < CAPACITY; i++)
		if(frame[i] == -1)
			return 1;
	return 0;
}
int contains(int frame[3], int ele)
{
	int i;
	for(i = 0; i < 3; i++)
		if(ele == frame[i])
			return 1;
	return 0;
}
void LRU(int frame[CAPACITY], int ref[], int n)
{
	cout << "\nLeast Recently Used\n";
	int count[CAPACITY] = {0, 0, 0};
	int i, j, k = 0;
	faults = hits = 0;
	int index;
	for(i = 0; i < n; i++)
	{
		if(contains(frame, ref[i]))
		{
			hits++;
			for(int temp = 0; temp < CAPACITY; temp++)
			{
				if(frame[temp] == ref[i])
				{
					count[temp] = i;
					break;
				}
			}
		}
		else if(empty(frame))
		{
			faults++;
			frame[k++] = ref[i];
		}
		else
		{
			index = 0;
			faults++;
			int min = count[0];
			for(j = 0; j < CAPACITY; j++)
				if(min > count[j])
				{
					min = count[j];
					index = j;
				}
			frame[index] = ref[i];
			count[index] = i;
		}
	}
	cout << "Hits: " << hits << endl;
	cout << "Faults: " << faults << endl;
}
void OPTIMAL(int frame[CAPACITY], int ref[], int n)
{
	cout << "\nOPTIMAL\n";
	int i = 0, j, k;
	faults = hits = 0;
	int temp = 0;
	int index;
	for(i = 0; i < n; i++)
	{
		if(contains(frame, ref[i]))
		{
			hits++;
		}
		else if(empty(frame)) // for first three elements
		{
			faults++;
			frame[temp++] = ref[i];
		}
		else
		{
			faults++;
			index = check(frame, ref, n, i); // check which frames value will be needed furthest in the reference string
			// cout << "Frame index swapped: " << index << endl;
			frame[index] = ref[i];
		}
	}
	cout << "Hits: " << hits << endl;
	cout << "Faults: " << faults << endl;
}
void FIFO(int frame[CAPACITY], int ref[], int n)
{
	int i, j, k;
	cout << "\nFIFO\n";
	front = rear = faults = hits = 0;
	for(i = 0; i < n; i++)
	{
		if(contains(frame, ref[i]))
			hits++;
		else if(empty(frame)) // for first three cases
		{
			faults++;
			frame[rear] = ref[i];
			rear = (rear + 1) % CAPACITY;
		}
		else
		{
			faults++;
			frame[front] = ref[i];
			front = (front + 1) % CAPACITY;
		}
	}
	cout << "Hits: " << hits;
	cout << "\nFaults: " << faults << endl;
}
int main()
{
	cout << endl;
	int i, j, k;
	cout << "No. of elements: ";
	int n;
	cin >> n;

	cout << "Enter the reference string: ";
	int ref[n];
	int frame[CAPACITY];
	for(i = 0; i < n; i++)
	{
		cin >> ref[i];
	}
	init_frame(frame);
	FIFO(frame, ref, n);

	init_frame(frame);
	OPTIMAL(frame, ref, n);

	init_frame(frame);
	LRU(frame, ref, n);

	cout << endl;
}