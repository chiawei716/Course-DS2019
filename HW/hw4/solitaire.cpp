#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

// Dictionary for cards;
static char cards[13][3] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

struct Node
{
	int value;
	struct Node *next;
};

struct List
{
	struct Node *head;
	struct Node *tail;
};

bool isEmpty(struct List*);
void genDeck(struct List*);
struct Node* genNode(int);
void pushNode(struct List*, struct Node*);
void deleteNode(struct List*);
void showCards(struct Node*);
void moveNode(struct List*);

int main()
{
	struct List *deck = new struct List;
	deck->head = NULL;
	deck->tail = NULL;

	genDeck(deck);

	int target = 12;
	while(target >= 0)
	{
		// Show deck	
		showCards(deck->head);
		printf("\n");

		// If first card is target, remove it. Or, move it to tail
		if(deck->head->value == target)
		{
			deleteNode(deck);
			target--;
		}
		else
			moveNode(deck);
	}
}

// Check if a linked list is empty
bool isEmpty(struct List* list)
{
	if(list->head == NULL) return true;
	else return false;
}

// Randomly generate deck
void genDeck(struct List* list)
{
	srand(time(NULL));
	int left[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	for(int amount = 13; amount > 0; amount--)
	{
		int temp = rand() % amount;
		pushNode(list, genNode(left[temp]));
		left[temp] = left[amount - 1];
	}
	return;
}

// Return a new node with given value
struct Node* genNode(int value)
{
	struct Node *newNode = new struct Node;
	newNode->value = value;
	newNode->next = NULL;
	return newNode;
}

// Push a new node to the tail of a linked list
void pushNode(struct List* list, struct Node* newNode)
{
	if(isEmpty(list))
		list->head = newNode;
	else
		list->tail->next = newNode;
	list->tail = newNode;
	return;
}

// Delete first node of list
void deleteNode(struct List* list)
{
	if(isEmpty(list)) return;
	else if(list->head == list->tail)
	{
		delete list->head;
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		struct Node *temp = list->head->next;
		delete list->head;
		list->head = temp;
	}
	return;
}

// Move first node to tail
void moveNode(struct List* list)
{
	if(isEmpty(list) || list->head == list->tail) return;
	else
	{
		struct Node *temp = list->head->next;
		list->head->next = NULL;
		list->tail->next = list->head;
		list->tail = list->tail->next;
		list->head = temp;
	}
	return;
}

// Use recursive to print values of whole list
void showCards(struct Node* entry)
{
	printf("%s ", cards[entry->value]);
	if(entry->next != NULL)
		showCards(entry->next);
	return;
}
