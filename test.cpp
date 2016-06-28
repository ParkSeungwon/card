#include "game.h"
#include "card.h"
#include"player.h"
#include"hand.h"
using namespace std;

int main()
{
	Deck deck;
	deck.shuffle_deck();
	Player hand;
	hand += deck.distribute_card(true);
	hand += deck.distribute_card(true);
	hand += deck.distribute_card(true);
	hand += deck.distribute_card(true);
	hand += deck.distribute_card(true);
	hand += deck.distribute_card(true);
	hand += deck.distribute_card(true);

	//hand.show(0);
	cout << hand.show()
	cout << hand.predict(deck.deck);
	//hand.show(1);
	//hand.show(2);
}
