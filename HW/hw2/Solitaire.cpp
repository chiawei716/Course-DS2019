#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char** genShuffledDeck();
void showDeck(char**, const int&, const int&);
void swap(char*&, char*&);
void pushIndex(char**, int&);

// All cards
static char cards[13][3] = {
	"K", "Q", "J", "10", "9", "8", "7", "6", "5", "4", "3", "2", "A"
};

using std::cout;
using std::endl;
int main()
{
	// Get shuffled deck
	char** deck = genShuffledDeck();

	// Draw cards
	int target = 0;	// the one we want to draw
	int front = 0;
	int rear = 12;
	while(true)
	{
		// Show deck
		showDeck(deck, front, rear);
		if(target == 12) break;
		
		// If target, remove it and change to next target
		if(strcmp(cards[target], deck[front]) == 0)
		{
			delete deck[front];
			deck[front] = NULL;
			pushIndex(deck, front);
			target++;
		}
		// If not, push the queue forward
		else{
			pushIndex(deck, front);
			pushIndex(deck, rear);
		}
	}
	return 0;
}

// Generate a shuffled deck
char** genShuffledDeck()
{
	// Cards have not been assigned
	char* left[13];
	for(int i = 0; i < 13; i++)
	{
		left[i] = new char[3];
		strcpy(left[i], cards[i]);
	}

	// Suffle (insert by random order)
	srand(time(NULL));
	char** shuffled = new char*[13];
	for(int i = 0; i < 13; i++)
	{
		//Decide the card
		int index = rand() % (13 - i);
		shuffled[i] = new char[3];
		strcpy(shuffled[i], left[index]);
		swap(left[index], left[12 - i]);
	}

	for(int i = 0; i < 13; i++) delete left[i];
	return shuffled;
}

// Show deck
void showDeck(char** deck, const int& front, const int& rear)
{
	int i = front;
	while(true)
	{
		if(deck[i] != NULL) cout << deck[i] << " ";
		if(i == rear) break;

		i++;
		if(i >= 13) i = 0;
	}
	cout << endl;
	return;
}

// Swap position of two cards
void swap(char*& a, char*& b)
{
	char* temp = a;
	a = b;
	b = temp;
	return;
}

// Push index forward
void pushIndex(char** queue, int& i)
{
	do{
		i++;
		if(i >= 13) i = 0;
	}while(queue[i] == NULL);
	return;
}
