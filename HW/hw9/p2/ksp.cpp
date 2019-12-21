#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Node
{
	string path;
	int cost;
	struct Node *next;
};

struct List
{
	struct Node* head;
};

string int_to_str(int n)
{
	string s;
	stringstream ss(s);
	ss << n;
	return ss.str();
}

void insert(struct List*, int, string);
void destruct(struct Node*);
void KSP(struct List*, int**, int, int, int, string, int, bool* visited = nullptr);

int main()
{
	// Input number of vertices
	int N;
	cin >> N;
	if(!cin || N < 2 || N > 100) return 0;

	// Input number of links
	int M;
	cin >> M;
	if(!cin) return 0;

	// Initialize adjacency matrix
	int **adjacencyMatrix = new int*[N];
	for(int i = 0; i < N; ++i)
	{
		adjacencyMatrix[i] = new int[N];
		for(int j = 0; j < N; ++j)
			adjacencyMatrix[i][j] = -1;
	}

	// Input links
	for(int i = 0; i < M; ++i)
	{
		int start, end, weight;
		cin >> start >> end >> weight;
		if(!cin || start < 1 || start > N || end < 1 || end > N || weight < 0) return 0;
		adjacencyMatrix[start - 1][end - 1] = weight;
	}

	// Input number of path
	int K;
	cin >> K;
	if(!cin) return 0;

	// Use linked list to store all path
	struct List *result = new struct List;
	result->head = nullptr;

	// Compute KSP
	KSP(result, adjacencyMatrix, N, -1, 0, "", 0);

	// Print answer
	struct Node *temp = result->head;
	cout << "\n";
	for(int i = 0; temp != nullptr && i < K; ++i, temp = temp->next)
	{
		for(int j = 0; j < (temp->path).length(); ++j)
			cout << temp->path[j] << " ";
		cout << "\n";
	}
	
	

	// Release memory
	destruct(result->head);
	for(int i = 0; i < N; ++i)
		delete[] adjacencyMatrix[i];
	delete[] adjacencyMatrix;
}

// Insert
void insert(struct List* list, int cost, string path)
{
	// If empty
	if(list->head == nullptr)
	{
		list->head = new struct Node;
		list->head->path = path;
		list->head->cost = cost;
		list->head->next = nullptr;
	}
	else
	{
		struct Node *temp = list->head;
		if(list->head->cost > cost)
		{
			list->head = new struct Node;
			list->head->path = path;
			list->head->cost = cost;
			list->head->next = temp;
			return;
		}
		else{
			while(temp->next != nullptr)
			{
				// If next one is larger
				if(temp->next->cost > cost)
				{
					struct Node *temp2 = temp->next;
					temp->next = new struct Node;
					temp->next->path = path;
					temp->next->cost = cost;
					temp->next->next = temp2;
					return;
				}
				temp = temp->next;
			}
		}
		// If this one is largest
		temp->next = new struct Node;
		temp->next->path = path;
		temp->next->cost = cost;
		temp->next->next = nullptr;
	}
	return;
}

// Release list memory
void destruct(struct Node* head)
{
	if(head == nullptr) return;

	if(head->next != nullptr)
		destruct(head->next);
	
	delete head;
	return;
}

// KSP
void KSP(struct List* list, int** matrix, int N, int from, int to, string path, int cost, bool* visited)
{
	// Initialize visited
	bool newVisit = false;
	if(visited == nullptr)
	{
		newVisit = true;
		visited = new bool[N];
		for(int i = 0; i < N; ++i)
		visited[i] = false;
	}

	bool *visited_cp = new bool[N];
	for(int i = 0; i < N; ++i)
		visited_cp[i] = visited[i];

	// Update state
	visited_cp[to] = true;
	path = path + int_to_str(to + 1);
	if(from != -1)
		cost = cost + matrix[from][to];
	else
		cost = 0;

	// If end
	if(to == N - 1) insert(list, cost, path);

	// or not
	else
	{
		for(int i = 0; i < N; ++i)
			if(!visited_cp[i] && matrix[to][i] != -1)
			{
				KSP(list, matrix, N, to, i, path, cost, visited_cp);
			}
	}

	delete[] visited_cp;
	if(newVisit) delete[] visited;
	return;
}
