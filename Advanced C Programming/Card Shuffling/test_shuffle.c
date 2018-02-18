// You may modify this file for testing but this file
// will not be submitted.
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "utility.h"
#include "shuffle.h"

int main(int argc, char ** argv)
{
  char deck[MAX_SIZE] = {'A', '2', '3', '4', 
			 '5', '6', '7', '8'};

  CardDeck orig_deck;
  bcopy(deck, orig_deck.cards, MAX_SIZE * sizeof(char));
  orig_deck.size = 4;
  repeat_shuffle(orig_deck, 2);
  return EXIT_SUCCESS;
}

