#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "shuffle.h"

int main(int argc, char ** argv) {
	char deck[MAX_SIZE] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

	CardDeck orig_deck = {
		.size = MAX_SIZE,
		.cards = {0}  // initialize all to 0 since it will be populated using memcpy(..)
	};
	memcpy(orig_deck.cards, deck, MAX_SIZE * sizeof(orig_deck.cards[0]));

	// Change the size to test the program.  If it is smaller than MAX_SIZE, some
	// cards are not used.  Assume the original deck has at least two cards.
	for (int size = 2; size <= 8; size ++) {
		printf("\n\n*** size = %d***\n", size);
		orig_deck.size = size; 
		shuffle(orig_deck);
	}
	return EXIT_SUCCESS;
}
