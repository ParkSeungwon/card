#pragma once
#include"card.h"
#include"hand.h"

class Game
{
public: 
	Game(int how_many_players);
	bool init_game();
	Hand player[7];
	int decide_first();
	int round();

protected:
	int player_count;
	Deck deck;
	int game_money;
	int call_money;
	int cur_round;
	int bet_count[7], money[7];
	enum Status { DIE, CALL, BET, BROKE, NOT_IN} status[7];

private:
	void think(int player);
	void human(int player);
	bool bet(int player, int money);
	void call(int player);
	void die(int player);
	void dealer(bool open_or_not);
	void show();
	void open_cards();

	int first_to_go;
};

