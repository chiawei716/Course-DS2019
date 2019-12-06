#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

struct Node
{
	char value;
	struct Node *next;
};

struct List
{
	struct Node *head;
	struct Node *tail;
};

bool isEmpty(struct List*);
bool isMember(struct Node*, char);
struct Node* genNode(char);
void insert(struct List*, int, struct Node*);
void push(struct List*, struct Node*);
void remove(struct List*);
void show(struct Node*);

int main()
{
	// Input number of groups
	int N;
	cin >> N;
	if(!cin) return 0;
	struct List **groups = new struct List*[N];
	
	// Input members of each group
	for(int i = 0; i < N; i++)
	{
		groups[i] = new struct List;
		groups[i]->head = NULL;
		groups[i]->tail = NULL;
		int M;
		cin >> M;
		if(!cin) return 0;
		for(int j = 0; j < M; j++){
			char val;
			cin >> val;
			push(groups[i], genNode(val));
		}
	}

	struct List *queue = new struct List;
	queue->head = NULL;
	queue->tail = NULL;

	char input[20];
	while(true)
	{
		//show(queue->head);
		//cout << endl;

		cin >> input;
		if(cin.eof()) break;

		// Dequeue
		if(strcmp(input, "DEQUEUE") == 0)
		{
			if(isEmpty(queue))
				cout << "The queue is empty.\n";
			else
			{
				cout << queue->head->value << endl;
				remove(queue);
			}
		}

		// Enqueue
		else if(strcmp(input, "ENQUEUE") == 0)
		{
			char value;
			cin >> value;
			if(!cin) return 0;

			if(isEmpty(queue)) push(queue, genNode(value));
			else
			{
				int belong = -1;
				for(int i = 0; i < N; i++)
					if(isMember(groups[i]->head, value)) belong = i;

				if(belong == -1) push(queue, genNode(value));
				else
				{
					int pos = 0;
					struct Node *iterator = queue->head;
					while(iterator != NULL)
					{
						if(isMember(groups[belong]->head, iterator->value)) break;
						iterator = iterator->next;
						pos++;
					}
					if(iterator == NULL)
						push(queue, genNode(value));
					else
						insert(queue, pos, genNode(value));
				}
			}
		}

		// Invalid input
		else
			return 0;
	}
	return 0;
}

// Check if linked list is empty
bool isEmpty(struct List* list)
{
	if(list->head == NULL) return true;
	else return false;
}

// Generate a node with given value
struct Node* genNode(char value)
{
	struct Node *newNode = new struct Node;
	newNode->value = value;
	newNode->next = NULL;
	return newNode;
}

// Insert a node to given position (right before it)
void insert(struct List* list, int pos, struct Node* newNode)
{
	if(isEmpty(list))
	{
		list->head = newNode;
		list->tail = newNode;
	}
	if(pos == 0)
	{
		newNode->next = list->head;
		list->head = newNode;
	}
	else
	{
		struct Node *iterator = list->head;
		for(int count = 1; count < pos; count++)
		{
			if(iterator->next != NULL)
				iterator = iterator->next;
			else
				break;
		}
		if(iterator == list->tail)
			list->tail = newNode;
		newNode->next = iterator->next;
		iterator->next = newNode;
	}
	return;
}

// Push a node at the tail of linked list
void push(struct List* list, struct Node* newNode)
{
	if(isEmpty(list))
	{
		list->head = newNode;
		list->tail = newNode;
	}
	else
	{
		list->tail->next = newNode;
		list->tail = newNode;
	}
	return;
}

// Remove the first node
void remove(struct List* list)
{
	if(isEmpty(list)) return;
	if(list->head == list->tail) list->tail = NULL;
	struct Node *temp = list->head->next;
	delete list->head;
	list->head =temp;
	return;
}

// Check if given value is included in a linked list
bool isMember(struct Node* node, char value)
{
	if(node->value == value) return true;
	if(node->next == NULL) return false;
	return isMember(node->next, value);
}

// Print out a linked list
void show(struct Node* head)
{
	if(head == NULL) return;
	cout << head->value << " ";
	show(head->next);
	return;
}
