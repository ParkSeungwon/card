#include "card.h"
#include"player.h"
#include"hand.h"
#include<algorithm>
using namespace std;

int main()
{
	Deck deck;
	deck.shuffle_deck();
	array<Card, 7> cds;
	copy_n(deck.deck.begin(), 7, cds.begin());
	Player pl;
	pl += deck.distribute_card(true);
	pl += deck.distribute_card(true);
	pl += deck.distribute_card(true);
	pl += deck.distribute_card(true);
	pl += deck.distribute_card(false);
	pl += deck.distribute_card(false);
	pl.show();
	cout << pl.predict(deck);
	//hand.show(0);
	//cout << hand.predict(deck);
	//hand.show(1);
	//hand.show(2);
}
