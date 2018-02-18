// do not modify this file
#include "utility.h"
#include <stdio.h>

void print_deck(CardDeck deck) {
	printf("[");
	int iter;
	for (iter = 0; iter < deck.size; iter ++)
	{
		printf("%c",  deck.cards[iter]);
	}
	printf("]");
}

void print_decks(CardDeck upper_deck, CardDeck lower_deck) {
	printf("upper deck:");
	print_deck(upper_deck);
	printf(" === lower deck: ");
	print_deck(lower_deck);
	printf("\n");
}
