#ifndef UTILITY_H
#define UTILITY_H
// do not modify this file
#define MAX_SIZE 8
typedef struct
{
  char cards[MAX_SIZE];
  int size; // actual size, must be between 0 and MAX_SIZE
  // if size < MAX_SIZE, some elements in cards are not used
} CardDeck;

void printDeck(CardDeck new_deck);

void print2Deck(CardDeck upper_deck, CardDeck lower_deck);

int power2(int n);

int powerkn(int k, int n);
#endif 
