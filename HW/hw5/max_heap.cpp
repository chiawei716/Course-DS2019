#include <iostream>
using namespace std;

void parent_child(int*, int, int);
void maxheapify(int*, int);

int main()
{
	// time of testing
	int T;
	cin >> T;
	if(!cin || T > 10 || T < 1) return 0;
	int result[T];	// result

	for(int i = 0; i < T; ++i)
	{
		// number of rows
		int M;
		cin >> M;
		if(!cin || M > 1000000 || M < 1) return 0;
		int *rows = new int[ M ];

		// number of people
		int N;
		cin >> N;
		if(!cin || N > 1000000 || N < 1) return 0;

		// number of vacant seats of each rows
		for(int j = 0; j < M; ++j)
		{
			cin >> rows[j];
			if(!cin || rows[j] > 1000000 || rows[j] < 0) return 0;
		}

		// Maxheapifying
		maxheapify(rows, M);

		// Get sum the maximum one (root), while minus 1 each time
		result[i] = 0;
		for(int j = 0; j < N; ++j)
		{
			result[i] += rows[0];
			rows[0]--;
			parent_child(rows, M, 0);	// maxheapify again
		}

		delete[] rows;
	}

	// Show result
	for(int i = 0; i < T; ++i)
		cout << result[i] << endl;
}

void parent_child(int* heap, int size, int index_p)
{
	if((index_p+1)*2 >= size) return;

	// Left child
	if(heap[index_p] < heap[(index_p+1)*2-1])
	{
		int temp = heap[index_p];
		heap[index_p] = heap[(index_p+1)*2-1];
		heap[(index_p+1)*2-1] = temp;
		parent_child(heap, size, (index_p+1)*2-1);
	}
	// Right child
	else if(heap[index_p] < heap[(index_p+1)*2])
	{
		int temp = heap[index_p];
		heap[index_p] = heap[(index_p+1)*2];
		heap[(index_p+1)*2] = temp;
		parent_child(heap, size, (index_p+1)*2);
	}
	return;
}

void maxheapify(int* heap, int size)
{
	int pos = size;
	while(pos > 1)
	{
		if(heap[pos-1] > heap[pos/2 - 1])
		{
			int temp = heap[pos - 1];
			heap[pos - 1] = heap[pos/2 - 1];
			heap[pos/2 - 1] = temp;
			parent_child(heap, size, pos/2 - 1);
		}
		pos--;
	}
	return;
}
