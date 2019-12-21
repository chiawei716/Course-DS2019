#include <iostream>
#include <iomanip>
using namespace std;

struct Activity
{
	int index;
	int start;
	int end;
	int duration;
};

int max(int a, int b)
{
	if(a == -1) return b;
	else if(b == -1) return a;

	if(a > b) return a;
	else return b;
}

int min(int a, int b)
{
	if(a == -1) return b;
	else if(b == -1) return a;

	if(a < b) return a;
	else return b;
}

int main()
{
	int last = 0;

	// Input N
	int N;
	cin >> N;
	if(!cin || N <= 0 || N >= 100) return 0;

	// Initialize adjacency matrix
	struct Activity *activities = new struct Activity[N];
	int **adjacencyMatrix = new int*[N];
	for(int i = 0; i < N; ++i)
	{
		adjacencyMatrix[i] = new int[N];
		for(int j = 0; j < N; j++)
			adjacencyMatrix[i][j] = -1;
	}

	for(int i = 0; i < N; ++i)
	{
		// input four numbers
		int index, start, end, duration;
		cin >> index >> start >> end >> duration;
		if(!cin) return 0;

		// store
		activities[i].index = index;
		activities[i].start = start;
		activities[i].end = end;
		activities[i].duration = duration;
		adjacencyMatrix[start][end] = duration;
		if(start > last) last = start;
		if(end > last) last = end;
	}
	last++;

	int *ee = new int[last];
	int *le = new int[last];
	for(int i = 0; i < last; ++i)
	{
		ee[i] = -1;
		le[i] = -1;
	}

	// Compute ee
	ee[0] = 0;
	for(int i = 0; i < last; ++i)
		for(int j = 0; j < last; ++j)
			if(adjacencyMatrix[i][j] != -1)
				ee[j] = max(ee[i] + adjacencyMatrix[i][j], ee[j]);

	// Compute le
	le[last - 1] = ee[last - 1];
	for(int i = last - 1; i >= 0; --i)
		for(int j = 0; j < last; ++j)
			if(adjacencyMatrix[j][i] != -1)
				le[j] = min(le[i] - adjacencyMatrix[j][i], le[j]);

	// Print event table
	cout << "\nevent\tee\tle\n";
	for(int i = 0; i < last; ++i)
		cout << i << "\t" << ee[i] << "\t" << le[i] << "\n";

	// Compute e & l & slack
	int *e = new int[N];
	int *l = new int[N];
	int *slack = new int[N];
	for(int i = 0; i < N; ++i)
	{
		e[i] = ee[activities[i].start];
		l[i] = le[activities[i].end] - activities[i].duration;
		slack[i] = l[i] - e[i];
	}

	// Print activity table
	cout << "\nact.\te\tl\tslack\tcritical\n";
	for(int i = 0; i < N; ++i)
		cout << activities[i].index << "\t" << e[i] << "\t" << l[i] << "\t" << slack[i] << "\t" << (slack[i] == 0 ? "Yes\n" : "No\n");

	// Print critical network
	cout << "\n";
	for(int i = 0; i < N; ++i)
		if(slack[i] == 0)
			cout << activities[i].index << " ";
	cout << "\n";

	// Release memory
	for(int i = 0; i < N; ++i)
		delete[] adjacencyMatrix[i];
	delete[] adjacencyMatrix;
	delete[] activities;
	delete[] ee;
	delete[] le;
	delete[] e;
	delete[] l;
	delete[] slack;
	return 0;
}


