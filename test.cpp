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
	pl += deck.distribute_card(true);
	pl += deck.distribute_card(false);
	pl += deck.distribute_card(false);
	pl.show();
	pl.open_cards();
	Player pl2;
	deck.distribute_card(true);
	deck.distribute_card(true);
	deck.distribute_card(true);
	deck.distribute_card(true);
	deck.distribute_card(true);
	deck.distribute_card(true);
	deck.distribute_card(true);
	deck.distribute_card(true);
	deck.distribute_card(true);
	deck.distribute_card(true);
	deck.distribute_card(true);
	deck.distribute_card(true);
	deck.distribute_card(true);
	deck.distribute_card(true);
	pl2 += deck.distribute_card(true);
	pl2 += deck.distribute_card(true);
	pl2 += deck.distribute_card(true);
	pl2 += deck.distribute_card(true);
	//pl2 += deck.distribute_card(true);
	pl2 += deck.distribute_card(false);
	pl2 += deck.distribute_card(false);
	pl2.show();
	auto pa = pl.predict(deck, pl2);
	cout << pa.first << ' ' << pa.second << endl;
	//pl2.open_cards();
	if(pl < pl2) cout << "player 2 win" << endl;
	else cout << "player 1 win " << endl;
	cout << pl.predict(deck).first << endl;
	cout << pl.predict(deck, pl2).first << endl;
	//hand.show(0);
	//cout << hand.predict(deck);
	//hand.show(1);
	//hand.show(2);
}
