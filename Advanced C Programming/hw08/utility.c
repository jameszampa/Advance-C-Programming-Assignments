// do not modify this file
#include "utility.h"
#include <stdio.h>

void printDeck(CardDeck deck)
{
  printf("[");
  int iter;
  for (iter = 0; iter < deck.size; iter ++)
    {
      printf("%c",  deck.cards[iter]);
    }
  printf("]\n");
}

void print2Deck(CardDeck upper_deck, CardDeck lower_deck)
{
  printf("upper deck:");
  printDeck(upper_deck);
  printf(" === lower deck: ");
  printDeck(lower_deck);
  printf("\n");
}

int power2(int n)
{
  int product = 1;
  while (n > 0)
    {
      product *= 2;
      n --;
    }
  return product;
}

int powerkn(int k, int n)
{
  int product = 1;
  while  (n > 0)
    {
      product *= k;
      n --;
    }
  return product;
}
