#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// transfer int to string
string int_to_str(int &n)
{
	string s;
	stringstream ss(s);
	ss << n;
	return ss.str();
}

int main()
{
	// Read several cases til eof
	while(!cin.eof())
	{
		// input number of vertices
		int Nv;
		cin >> Nv;
		if(!cin || Nv < 2 || Nv > 10) return 0;

		// Initialize adjacency matrix
		int **adjacencyMatrix = new int*[Nv];
		for(int i = 0; i < Nv; ++i)
		{
			adjacencyMatrix[i] = new int[Nv];
			for(int j = 0; j < Nv; ++j)
			{
				if(i == j) adjacencyMatrix[i][j] = 0;	// vertice itself
				else adjacencyMatrix[i][j] = -1;		// -1 represent infinity
			}
		}

		// input number of edges
		int Ne;
		cin >> Ne;
		for(int i = 0; i < Ne; ++i)
		{
			// input edges
			int a, b, weight;
			cin >> a >> b >> weight;
			if(!cin || weight < 0 || a < 0 || b < 0) return 0;
			
			// store edges into adjacency matrix
			adjacencyMatrix[a][b] = weight;
		}

		// initializing data
		int count = 0;
		bool *visited = new bool[Nv];
		int *distance = new int[Nv];
		string *path = new string[Nv];
		for(int i = 0; i < Nv; ++i)
		{
			visited[i] = false;
			distance[i] = -1;	// infinitly far
			path[i] = new char[Nv];
		}

		while(count < Nv)
		{
			// Start with V0
			if(count == 0)
			{
				distance[0] = 0;
				visited[0] = true;
				path[0] = "0";

				// update others' distance
				for(int i = 1; i < Nv; ++i)
					if(adjacencyMatrix[0][i] != -1)
					{
						distance[i] = adjacencyMatrix[0][i];
						path[i] = path[0] + int_to_str(i);
					}
				count++;
				continue;
			}

			// other vertices ( choose the closest one )
			int target = -1;
			int dist = -1;
			for(int i = 1; i < Nv; i++)
			{
				// not visited yet
				if(!visited[i])
				{
					if(target == -1 && distance[i] != -1)
					{
						target = i;
						dist = distance[i];
					}
					else
						// closer one
						if(dist > distance[i] && distance[i] != -1)
						{
							target = i;
							dist = distance[i];
						}
				}
			}

			// if no vertices could reach
			if(target == -1) break;
			// if vertice chosen
			else
			{
				count++;
				visited[target] = true;
				for(int i = 0; i < Nv; ++i)
					if(adjacencyMatrix[target][i] != -1 && !visited[i])
					{
						if(distance[i] == -1 || distance[i] > distance[target] + adjacencyMatrix[target][i])
						{
							distance[i] = distance[target] + adjacencyMatrix[target][i];
							path[i] = path[target] + int_to_str(i);
						}
					}
			}
		}
		
		// Show result
		cout << endl;
		for(int i = 1; i < Nv; ++i)
		{
			if(distance[i] == -1) cout << "Impossible\n";
			else{
				for(int j = 0; j < path[i].length(); ++j)
				{
					if(j != 0) cout << ",";
					cout << path[i][j];
				}
				cout << " " << distance[i] << endl;
			}
		}
		cout << endl;


		// Delete matrixes
		for(int i = 0; i < Nv; ++i)
		{
			delete[] adjacencyMatrix[i];
		}
		delete[] adjacencyMatrix;
		delete[] visited;
		delete[] distance;
		delete[] path;
	}
	return 0;
}
