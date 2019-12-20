#include <iostream>
using namespace std;

struct AdjacencyNode
{
	int value;
	struct AdjacencyNode *next;
};

struct AdjacencyList
{
	int size;
	struct AdjacencyNode **heads;
};

struct AdjacencyList* newList(int);				// Initialize a new adjacency list
void addEdge(struct AdjacencyList*, int, int);	// Add an edge to list
void addEdge_node(struct AdjacencyNode*&, int);	// Add an edge to a node sequence
void showList(struct AdjacencyList*);			// Show adjacency list
void dfs();
int* getBipartite(struct AdjacencyList*);		// Get bipartite sets, or nullptr if no one
void showBipartite(int*, int);					// Show bipartite sets
void deleteList(struct AdjacencyList*&);		// Delete an adjacency list
void deleteNode(struct AdjacencyNode*);			// Delete a node sequence
int main()
{
	// Input number of vertices
	int Nv;
	cin >> Nv;
	if(!cin || Nv < 2)
	{
		cout << "Invalid input.\n";
		return 0;
	}

	// Input number of edges
	int Ne;
	cin >> Ne;
	if(!cin || Ne > Nv * ( Nv - 1 ) / 2)
	{
		cout << "Invalid input.\n";
		return 0;
	}

	// Consturct new list
	struct AdjacencyList *adjacencyList = newList(Nv);

	// Input edges
	for(int i = 0; i < Ne; ++i)
	{
		int a, b;
		cin >> a >> b;
		if(!cin || a >= Nv || a < 0 || b >= Nv || b < 0)
		{
			cout << "Invalid input.\n";
			return 0;
		}

		addEdge(adjacencyList, a, b);
	}

	// Show adjacency list
	showList(adjacencyList);

	// Compute bipartite
	int *bipartite = getBipartite(adjacencyList);
	
	// Show bipartite sets
	showBipartite(bipartite, Nv);

	deleteList(adjacencyList);
}

// Initialize a new adjacency list
struct AdjacencyList* newList(int Nv)
{
	struct AdjacencyList* newList = new struct AdjacencyList;
	newList->heads = new struct AdjacencyNode*[Nv];
	for(int i = 0; i < Nv; ++i)
		newList->heads[i] = nullptr;
	newList->size = Nv;
	return newList;
}

// Add an edge to list (two adjacency relations - undirected)
void addEdge(struct AdjacencyList* list, int a, int b)
{
	addEdge_node(list->heads[a], b);
	addEdge_node(list->heads[b], a);
	return;
}

// Add an edge to a node sequence
void addEdge_node(struct AdjacencyNode*& node, int value)
{
	// If already null
	if(node == nullptr)
	{
		node = new struct AdjacencyNode;
		node->value = value;
		node->next = nullptr;
	}
	// Else or not been added
	else
	{
		// Go to end
		struct AdjacencyNode *temp = node;
		while(temp->next != nullptr)
		{
			if(temp->value == value) return;
			temp = temp->next;
		}
		temp->next = new struct AdjacencyNode;
		temp->next->value = value;
		temp->next->next = nullptr;
	}
	return;
}

// Show adjacency list
void showList(struct AdjacencyList* list)
{
	// Proccess on all heads
	struct AdjacencyNode* head = list->heads[0];
	for(int i = 0; i < list->size; ++i, head = list->heads[i])
	{
		// head
		cout << i << " -> ";
		
		// first node
		if(head != nullptr)
		{
			cout << head->value;
			head = head->next;
		}

		// other nodes
		while(head != nullptr)
		{
			cout << " -> " << head->value;
			head = head->next;
		}

		cout << "\n";
	}
	return;
}

int** DFS_tree(struct AdjacencyList* list)
{
	// parent, low, visit
	int **result;
	int time = 0;
	result = new int[3];
	for(int i = 0; i < 3; ++i)
	{
		result[i] = new int[list->size];
		for(int j = 0; j < list->size; ++j)
			result[j] = -1;
	}

	for(int i = 0; i < list->size; ++i)
		DFS(result, list, list->heads[i], time);


}

void DFS(int** info, struct AdjacencyList* list, struct AdjacencyNode* i, int& time)
{
	info[2][i->value] = info[1][i->value] = ++time;
	
	struct AdjacencyNode* node = list->heads[i->value];
	while(node != nullptr)
	{
		// Iterator
		if(info[2][node->value] == -1)
		{
			info[0][node->value] = i->value;
			DFS(info, list, node, time);
		}

		// Update low information
		bool isAdjacent = false;
		struct AdjacencyNode* temp = list->heads[node->value];
		while(temp != nullptr)
		{
			if(temp->value == i->value)
			{
				isAdjacent = true;
				break;
			}
			temp = temp->next;
		}
		if(!(node->value == info[0][i->value] && isAdjacent))
		{
			info[1][i->value] = info[1][i->value] <= info[1][node->value] ? info[1][i->value] : info[1][node->value];
		}
	}
	return;
}

// Delete a adjacency list
void deleteList(struct AdjacencyList*& list)
{
	// Proccess on all heads with recursive function
	struct AdjacencyNode* head = list->heads[0];
	for(int i = 0; i < list->size; ++i, head = list->heads[i]) deleteNode(head);

	// Delete all
	delete[] list->heads;
	delete list;
	list = nullptr;

	return;
}

// Delete a node sequence
void deleteNode(struct AdjacencyNode* head)
{
	// If this is already null, return
	if(head == nullptr)
		return;

	// If next one isn't null, go forward first
	if(head->next != nullptr)
		deleteNode(head->next);

	// Delete this one, then return
	delete head;
	return;
}
