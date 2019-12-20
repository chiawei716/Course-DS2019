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

// Get bipartite sets, or nullptr if no one
int* getBipartite(struct AdjacencyList* list)
{
	int size = list->size;

	// Initial set1 with all vertices, set2 with none
	bool **set = new bool*[2];
	set[0] = new bool[size];
	set[1] = new bool[size];
	
	for(int i = 0; i < size; ++i)
	{
		set[0][i] = true;
		set[1][i] = false;
	}
	
	// Move nodes to set2 if adjacent
	struct AdjacencyNode* head = list->heads[0];
	for(int i = 0; i < size; ++i, head = list->heads[i])
	{
		// If vertice has no neighbor
		if(head == nullptr) continue;

		// vertice is in set1 ( not changed )
		if(set[0][i])
		{
			while(head != nullptr)
			{
				set[0][head->value] = false;
				set[1][head->value] = true;
				head = head->next;
			}
		}
	}
	// Check nodes in set2 if adjacent with any other
	head = list->heads[0];
	for(int i = 0; i < size; ++i, head = list->heads[i])
	{
		// If vertice has no neighbor
		if(head == nullptr) continue;

		// vertice is in set2 ( not changed )
		if(set[1][i])
		{
			while(head != nullptr)
			{
				// Invalid
				if(set[1][head->value] == true) return nullptr;
				head = head->next;
			}
		}
	}

	// Valid, return an one dimension of result
	int *result = new int[size];
	for(int i = 0; i < size; ++i)
	{
		if(set[0][i]) result[i] = 1;
		else result[i] = 2;
	}
	delete[] set[0];
	delete[] set[1];
	delete[] set;

	return result;
}

// Show bipartite sets
void showBipartite(int* bipartite, int Nv)
{
	if(bipartite == nullptr)
	{
		cout << "false\n";
		return;
	}

	bool first = true;
	cout << "Set1: ";
	for(int i = 0; i < Nv; i++)
		if(bipartite[i] == 1)
		{
			if(first) 
			{
				cout << i;
				first = false;
			}
			else cout << ", " << i;
		}
	cout << "\n";

	first = true;
	cout << "Set2: ";
	for(int i = 0; i < Nv; i++)
		if(bipartite[i] == 2)
		{
			if(first)
			{
				cout << i;
				first = false;
			}
			else cout << ", " << i;
		}
	cout << "\n";
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
