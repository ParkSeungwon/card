#include<map>
#include<random>
#include<algorithm>
#include<iostream>
#include<exception>
#include<string>
#include"card.h"
#include"combi.h"
#include"hand.h"
using namespace std;
constexpr const char* Card::glyph[4];
constexpr const char Card::g[4];

int main()
{
	Deck deck;
	deck.shuffle_deck();
	Hand player1, player2, player3;

	cout << "Player 1 has : ";
	for(int i=0; i<7; i++) cout << deck[i] << ' ';
	cout << endl;
	cout << "Player 2 has : ";
	for(int i=7; i<14; i++) cout << deck[i] << ' ';
	cout << endl;
	for(int i=0; i<4; i++) {
		player1 += deck.distribute_card(true);
		player2 += deck.distribute_card(true);
		player3 += deck.distribute_card(true);
	}	
	for(int i=0; i<2; i++) {
		player1 += deck.distribute_card(false);
		player2 += deck.distribute_card(false);
		player3 += deck.distribute_card(false);
	}	
	
	player1.show();
	player2.show();
	player3.show();
	cout << player1.predict(deck.deck) << endl;
	cout << player1.predict(deck.deck, player2.face()) << endl;
	cout << player1.predict(deck.deck, player3.face()) << endl;
	cout << endl;
	cout << player2.predict(deck.deck, player1.face()) << endl;
	cout << player2.predict(deck.deck) << endl;
	cout << player2.predict(deck.deck, player3.face()) << endl;
	cout << endl;
	cout << player3.predict(deck.deck, player1.face()) << endl;
	cout << player3.predict(deck.deck, player2.face()) << endl;
	cout << player3.predict(deck.deck) << endl;

//	player1.read_hand();
//	player2.read_hand();
//	player3.read_hand();
}


