#include<map>
#include<random>
#include<algorithm>
#include<iostream>
#include<exception>
#include<string>
#include"card.h"
#include"combi.h"
using namespace std;


Deck::Deck()
{
	Card card;
	for(int i=1, k=0; i<14; i++) {
		for(char a : {'C', 'D', 'H', 'S'}) {
			card.n = i;
			card.c = a;
			deck[k++] = card;
		}
	}
}

void Deck::shuffle_deck()
{ 
	for(auto& a : deck) a.show(false);
	shuffle(deck.begin(), deck.end(), random_device());
	top = 0;
}
	
Card Deck::distribute_card(bool open)
{
	if(top < 52) {
		deck[top].show(open);
		return deck[top++];
	} else throw No_card_exception();
}

