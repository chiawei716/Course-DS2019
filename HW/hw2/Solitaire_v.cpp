#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;

vector<char*>* genSuffledDeck();    // Generate a shuffled deck

// All cards
static char cards[13][5] = {"K", "Q", "J", "10", "9", "8", "7", "6", "5", "4", "3", "2", "A"};

int main()
{
    // Get shuffled deck
    vector<char*>* deck = genSuffledDeck();

    // Draw cards
    int target = 0; // the one we want to draw
    do{
        // Show the deck
        for(int i = 0; i < deck->size(); i++)
            cout << deck->at(i) << " ";
        cout << endl;

        // Check the first card
        // If target, remove it and change to next target
        if(strcmp(cards[target], deck->at(0)) == 0)
        {
            deck->erase(deck->begin());
            target++;
        }
        // If not, put it to the last
        else
        {
            deck->push_back(deck->at(0));
            deck->erase(deck->begin());
        }
    }while(deck->size() != 0);  // break when the deck is empty

    return 0;
}

// Generate a shuffled deck
vector<char*>* genSuffledDeck()
{
    // Cards have not been assigned
    vector<char*> left;
    for(int i = 0; i < 13; i++)
        left.push_back(cards[i]);

    // Shuffle (insert by random order)
    srand(time(NULL));
    vector<char*>* shuffled = new vector<char*>();
    for(int i = 0; i < 13; i++)
    {
        // Decide the card
        int index = rand() % (13 - i);
        char* temp = new char[5];
        strcpy(temp, left.at(index));

        // Add to shuffled deck, and remove from left one
        shuffled->push_back(temp);
        left.erase(left.begin() + index);
    }
    return shuffled;
}
