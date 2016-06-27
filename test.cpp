#include "game.h"
#include "card.h"
using namespace std;

int main()
{
	Deck deck;
	deck.shuffle_deck();
	Hand hand;
	hand += deck.distribute_card(true);
	hand += deck.distribute_card(true);
	hand += deck.distribute_card(true);
	hand += deck.distribute_card(true);
	hand += deck.distribute_card(true);
	hand += deck.distribute_card(true);
	hand += deck.distribute_card(true);

	hand.show(0);
	cout << hand.read_final();
	hand.show(1);
	//hand.show(2);
}
