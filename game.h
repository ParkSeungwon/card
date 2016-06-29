#pragma once
#include"player.h"


class Game
{
public: 
	Game(int how_many_players);
	bool init_game();
	Player player[7];
	int decide_first();
	int round();
	void show(int player);

protected:
	int player_count;
	Deck deck;
	enum Status { DIE, CALL, BET, BROKE, NOT_IN} status[7];
	int bet_count[7], money[7], bet_money[7];
	int game_money;
	int call_money, call_count;
	int cur_round, cur_player_count;

private:
	void think(int player);
	void human(int player);
	bool bet(int player, int money);
	void call(int player);
	void die(int player);
	void dealer(bool open_or_not);
	void open_cards();

	int first_to_go;
};

