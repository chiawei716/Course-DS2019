#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

void heightUnion(int*, int*, int, int);
int collapsingFind(int*, int);

int main()
{
	// number of trees
	int T;
	cin >> T;
	if(!cin || T < 1 || T > 100) return 0;
	int *parent = new int[101];
	int *height = new int[101];

	for(int i = 0; i < T; ++i)
	{
		// number of nodes in a tree
		int N;
		cin >> N;
		if(!cin || N < 1 || N > 100) return 0;
				
		// root & height
		int R, H;
		cin >> R >> H;
		if(!cin || R < 0 || R > 100 || H > -1 || H < -100) return 0;
		parent[R] = -1;
		height[R] = -H;

		// nodes
		for(int j = 0; j < N-1; ++j)
		{
			// node
			int node;
			cin >> node;
			if(!cin || node < 0 || node > 100) return 0;

			// parent
			int p;
			cin >> p;
			if(!cin || p < 0 || p > 100) return 0;
			parent[node] = p;
		}
	}

	// Use vector to store result
	vector<int> result;
	result.clear();

	char command[6];
	while(cin >> command)
	{
		if(!cin) return 0;
		
		// Union
		if(strcmp(command, "UNION") == 0)
		{
			int a, b;
			cin >> a >> b;
			if(!cin || a < 0 || a > 100 || b < 0 || b > 100) return 0;
			
			heightUnion(parent, height, a, b);
		}
		else if(strcmp(command, "FIND") == 0)
		{
			int a;
			cin >> a;
			if(!cin || a < 0 || a > 100) return 0;
			
			result.push_back(collapsingFind(parent, a));
		}
		else if(strcmp(command, "STOP") == 0)
		{
			for(int i = 0; i < result.size(); ++i)
				cout << result.at(i) << endl;
			break;
		}
		else
			break;
	}
}

void heightUnion(int* parent, int* height, int i, int j)
{
	// If any isn't root
	if(parent[i] != -1 || parent[j] != -1) return;

	// Hi > Hj
	if(height[i] > height[j])
	{
		parent[j] = i;
		height[j] = 0;
	}
	// Hi < Hj
	else if(height[i] < height[j])
	{
		parent[i] = j;
		height[i] = 0;
	}
	// Hi = Hj
	else if(height[i] == height[j])
	{
		parent[j] = i;
		height[j] = 0;
		height[i] += 1;
	}
	return;
}

int collapsingFind(int* parent, int element)
{
	int movement = 0;
	
	// Find root
	int trail = element;
	while(parent[trail] != -1)
	{
		trail = parent[trail];
		movement++;	// traversed
	}
	int root = trail;

	// Reset link
	trail = element;
	while(parent[trail] != -1)
	{
		if(parent[parent[trail]] == -1) break;
		int temp = parent[trail];
		parent[trail] = root;
		trail = temp;
		movement++;
	}
	return movement;
}

