#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Queue_Node
{
	char data;
	struct Queue_Node* next;
};

struct Queue
{
	struct Queue_Node* head;
	struct Queue_Node* tail;
};	

struct Group
{
	int size;
	char member[26];
};

void invalid_input();
bool ifEmpty(const struct Queue&);
int getGroup(const struct Group*, const int&, const char&);
void dequeue(struct Queue&);
void enqueue(struct Queue&, struct Group*, const int&, const char&);

int main()
{
	// Enter number of groups
	int g_num;
	printf("Number of groups: ");
	if(scanf("%d", &g_num) == 0 || g_num < 1 || g_num > 26) invalid_input();

	// Enter member of groups
	struct Group groups[g_num];
	for(int i = 0; i < g_num; i++)
	{
		if(scanf("%d", &groups[i].size) == 0 || groups[i].size < 1 || groups[i].size > 26)
			invalid_input();
		for(int j = 0; j < groups[i].size; j++)
		{
			char mem;
			scanf(" %c", &mem);
			groups[i].member[j] = mem;
		}
	}

	// Queueing
	char person;
	char command[10];
	struct Queue queue = {NULL, NULL};
	while(scanf("%s", command) != EOF)
	{
		// dequeue
		if(strcmp(command, "DEQUEUE") == 0)
			dequeue(queue);

		// enqueue
		else if(strcmp(command, "ENQUEUE") == 0)
		{
			scanf(" %c", &person);
			enqueue(queue, groups, g_num, person);
		}
	}
}

void invalid_input()
{
	printf("Invalid input. The program is terminated.\n");
	exit(0);
}

bool ifEmpty(const struct Queue& queue)
{
	if(queue.head == NULL && queue.tail == NULL)
		return true;
	else
		return false;
}

int getGroup(const struct Group* groups, const int& g_num, const char& target)
{
	for(int i = 0; i < g_num; i++)
		for(int j = 0; j < groups[i].size; j++)
			if(target == groups[i].member[j])	
				return i;
	return -1;
}

void dequeue(struct Queue& queue)
{
	// If the queue is empty
	if(ifEmpty(queue))
		printf("Queue is empty.\n");

	// Print the first one, and remove it
	else
	{
		printf("%c\n", queue.head->data);
		if(queue.head == queue.tail)
		{
			free(queue.head);
			queue.head = NULL;
			queue.tail = NULL;
		}
		else
		{
			Queue_Node* temp = queue.head;
			queue.head = queue.head->next;
			free(temp);
		}
	}
}

void enqueue(struct Queue& queue, struct Group* groups, const int& g_num, const char& data)
{
	struct Queue_Node* new_node = (struct Queue_Node*) malloc(sizeof(*new_node));
	new_node->data = data;

	// If the queue is empty
	if(ifEmpty(queue))
	{
		queue.head = new_node;
		queue.tail = queue.head;
		queue.head->data = data;
		return;
	}
	else
	{
		int group = getGroup(groups, g_num, data);
		
		// If not belongs to any group, add to the end of the queue
		if(group == -1)
		{
			new_node->next = NULL;
			queue.tail->next = new_node;
			queue.tail = new_node;
			return;
		}
		// Or find one in same group, insert it
		else{
			struct Queue_Node* last = NULL;
			struct Queue_Node* next = queue.head;
			while(true)
			{
				if(next == NULL)
				{
					new_node->next = NULL;
					queue.tail->next = new_node;
					queue.tail = new_node;
					return;
				}

				for(int i = 0; i < groups[group].size; i++)
					if(next->data == groups[group].member[i])
					{
						if(last != NULL)
							last->next = new_node;
						if(next == queue.head)
							queue.head = new_node;
						new_node->next = next;
						return;
					}
				
				last = next;
				next = next->next;
			}
		}
	}
}