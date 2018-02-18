#include "shuffle.h"
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// You may add more functions in this file.
void _call_interleave();
void _call_shuffle();
void helper();

void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck) 
{
	for(int n = 0; n < orig_deck.size - 1; n++) // number of pairs
	{	
		int card_index = 0;
		int u = 0;

		for( ; u <= n; u++) // upper_deck pairs
		{
			upper_deck[n].cards[card_index] = orig_deck.cards[u];
			card_index++;
			upper_deck[n].size = card_index;
		}
		
		card_index = 0;

		int l = u;

		for( ; l <= orig_deck.size - 1; l++) // lower_deck pairs
		{
			lower_deck[n].cards[card_index] = orig_deck.cards[l];
			card_index++;
			lower_deck[n].size = card_index;
		}
	}	
}
void _helper(CardDeck upper_deck, CardDeck lower_deck, CardDeck comb_deck, int index_low, int index_up, int k)
{
	if(upper_deck.size == index_up && lower_deck.size == index_low)
	{
		repeat_shuffle(comb_deck, k - 1);
	}
	else if(upper_deck.size == index_up)
	{
		for( ; index_low < lower_deck.size; index_low++)
		{
			comb_deck.cards[index_low + index_up] = lower_deck.cards[index_low];
		}
	
		_helper(upper_deck, lower_deck, comb_deck, index_low, index_up, k);
	}
	else if(lower_deck.size == index_low)
	{
		for( ; index_up < upper_deck.size; index_up++)
		{
			comb_deck.cards[index_low + index_up] = upper_deck.cards[index_up];
		}
		
		_helper(upper_deck, lower_deck, comb_deck, index_low, index_up, k);
	}
	else
	{
		comb_deck.cards[index_low + index_up] = upper_deck.cards[index_up];

		_helper(upper_deck, lower_deck, comb_deck, index_low, index_up + 1, k);

		comb_deck.cards[index_low + index_up] = lower_deck.cards[index_low];

		_helper(upper_deck, lower_deck, comb_deck, index_low + 1, index_up, k);
	}

}
void interleave(CardDeck upper_deck, CardDeck lower_deck) 
{
	//empty to satisfy pre-tester and homework 8 guidelines
	//i.e. function signatures must be the same
}

void shuffle(CardDeck orig_deck)
{
	//empty to satisfy pre-tester and homework 8 guidelines
	//i.e. function signatures must be the same
}

void repeat_shuffle(CardDeck orig_deck, int k)
{
	if(k <= 0)
	{
		printDeck(orig_deck);
	}
	else
	{
		_call_shuffle(orig_deck, k);
	}
}

void _call_interleave(CardDeck upper_deck, CardDeck lower_deck, int k)
{
	CardDeck comb_deck = 
	{
		.size = upper_deck.size + lower_deck.size,
		.cards = {0}
	};
	
	_helper(upper_deck, lower_deck, comb_deck, 0, 0, k);
}

void _call_shuffle(CardDeck orig_deck, int k)
{
	int numpairs = orig_deck.size - 1;

	CardDeck * upper_deck = upper_deck = malloc(sizeof(*upper_deck) * numpairs);
	CardDeck * lower_deck = lower_deck = malloc(sizeof(*lower_deck) * numpairs);

	// allocate memory
	if (upper_deck == NULL) 
	{
		free(lower_deck);
		EXIT_FAILURE;
	}
	if (lower_deck == NULL) 
	{
		free(upper_deck);
		EXIT_FAILURE;
	}

	// call divideDeck to fill upper_deck and lower_deck
	divide(orig_deck, upper_deck, lower_deck);
	
	numpairs--;
	while (numpairs >= 0)
	{
		_call_interleave(upper_deck[numpairs], lower_deck[numpairs], k);	
		numpairs--;
	}
	
	free(upper_deck);
	free(lower_deck);

}

