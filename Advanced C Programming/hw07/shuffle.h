// do not modify this file
#ifndef SHUFFLE_H
#define SHUFFLE_H
#include "utility.h"

void divide(CardDeck orig_deck, CardDeck* upper_deck, CardDeck* lower_deck);

void interleave(CardDeck upper_deck, CardDeck lower_deck);

void shuffle (CardDeck orig_deck);

void helper(CardDeck upper_deck, CardDeck lower_deck, CardDeck comb_deck, int index_low, int index_up);
#endif
