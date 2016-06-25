#include<map>
#include<random>
#include<algorithm>
#include<iostream>
#include<exception>
#include<string>
#include"card.h"
#include"combi.h"
using namespace std;
constexpr const char* Card::glyph[4];
constexpr const char Card::g[4];

int main()
{
	Deck deck;
	deck.shuffle_deck();
	array<Card, 7> player1, player2;

	cout << "Player 1 has : ";
	for(int i=0; i<7; i++) cout << deck[i] << ' ';
	cout << endl;
	cout << "Player 2 has : ";
	for(int i=7; i<14; i++) cout << deck[i] << ' ';
	cout << endl;
	for(auto& a : player1) a = deck.distribute_card(true);
	for(auto& a : player2) a = deck.distribute_card(true);
	
	Hand h1(player1);
	Hand h2(player2);
	h1.show();
	h2.show();
	cout << "Player " << (h1 < h2 ? 2 : 1) << " won !!" << endl;

	{
		Hand h;
		h.cards.push_back(deck.distribute_card(true));
		h.cards.push_back(deck.distribute_card(true));
		h.cards.push_back(deck.distribute_card(true));
		h.cards.push_back(deck.distribute_card(true));
		h.cards.push_back(deck.distribute_card(true));
		h.cards.push_back(deck.distribute_card(true));
		cout << h.predict(deck.deck) << endl;
	}
}


