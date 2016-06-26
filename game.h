#include"game.h"
class Game
{
public: 
	Game(int how_many_players);
	int init_game();

protected:
	int player_count;
	Deck deck;
	int game_money;
	int call_money;
	int bet_count[7], money[7];
	bool die[7];
};

