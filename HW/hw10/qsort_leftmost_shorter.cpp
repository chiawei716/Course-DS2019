#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#define SIZE 150000

using namespace std;

void swap(int*, int, int);	// Swap two numbers in an array
void qsort(int*, int, int);
void validate(int*);

int main()
{
	// Open file
	fstream file;
	file.open("data_150k.txt", ios::in);

	// Read & store data
	int data[SIZE];
	int count = 0;
	cout << "// Leftmost-shorter\n";
	cout << "Reading data............";
	while(file>>data[count]) count++;
	cout << "Done!!\n";

	// Time variables
	clock_t start, end;
	double cpu_time_used;

	// quick sort
	start = clock();
	qsort(data, 0, SIZE - 1);
	end = clock();

	// Check if sorted success
	validate(data);

	// Show spent time
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Use leftmost and shorter first execution time = %f\n\n", cpu_time_used);
	
	// Close file
	file.close();

	return 0;
}

// Swap two numbers in an array
void swap(int* data, int a, int b)
{
	int temp = data[a];
	data[a] = data[b];
	data[b] = temp;
	return;
}

// Quick sort
void qsort(int* data, int left, int right)
{
	if(left >= right || right <= left || left < 0 || right >= SIZE) return;

	// choose left most pivot
	int pivot = data[left];

	// two process variables
	int check = right;
	int insert = right;

	// check from right to left
	while(check != left)
	{
		// if >= pivot, swap it right
		if(data[check] >= pivot)
		{
			swap(data, check, insert);
			insert--;
		}
		
		// move leftward
		check--;
	}

	// move pivot to insert point
	swap(data, left, insert);

	// separate into two sublist (left first)
	if(insert - left < right - insert)
	{
		qsort(data, left, insert - 1);
		qsort(data, insert + 1, right);
	}
	else
	{
		qsort(data, insert + 1, right);
		qsort(data, left, insert - 1);
	}
}

// check if sorted success
void validate(int* data)
{
	for(int i = 0; i < SIZE - 1; ++i)
		if(data[i] > data[i + 1])
		{
			cout << "Failed!!\n";
			return;
		}
	cout << "Success!!\n";
}
