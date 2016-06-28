#include<iostream>
#include<algorithm>
#include"game.h"
#include"player.h"
using namespace std;
Game::Game(int many)
{
	player_count = many;
	for(int i=many; i<7; i++) player[i].status(NOT_IN);
	for(int i=0; i<player_count; i++) player[i].status(BET);
}

bool Game::init_game()
{
	int j=0, k;
	for(int i=0; i<player_count; i++) {
		if(player[i].money() <= 0) j++; 
		else k=i;
	}
	if(j == player_count -1) {
		cout << "winner is player " << k << endl;
		return false;
	}

	deck.shuffle_deck();
	game_money = 0;
	call_money = 0;
	cur_round = 3;
	for(int i=0; i<7; i++) bet_count[i] = 0;
	for(int i=0; i<player_count; i++) {
		if(player[i].status() != BROKE) {
			player[i].status(BET);
			player[i].clear();
			money[i] -= 10;
			game_money += 10;
		}
	}

	dealer(false);
	dealer(false);
	dealer(true);
	return true;
}

int Game::decide_first()
{
	int j = 0;
	for(int i=1; i<player_count; i++) {
		if(status[i] == CALL) player[i].read_hand();
		else player[i].point(-1);
	}
	for(int i=1; i<player_count; i++) if(player[j] < player[i]) j = i;
	first_to_go = j;
	return j;
}

int Game::round()
{
	int fr = decide_first();
	int k;
	call_money = 0;
	for(int i=0; i<player_count; i++) if(status[i] != BROKE) status[i] = BET;
	show();
	for(int n = fr; find(status, status+7, BET) != status+7; n++) {
		k = n % player_count;
		if(status[k] == CALL || status[k] == BET) {
			if(k == 0) human(k);
			else think(k);
		}
	}
	cout << endl << "Round " << ++cur_round << endl << endl;
	if(cur_round == 8) open_cards();
	else dealer(true);
	return cur_round;
}

void Game::open_cards()
{
	for(int i=0; i<player_count; i++) 
		if(status[i] == CALL) player[i].open_cards();
	int j = 0;
	for(int i=1; i<player_count; i++) if(player[j] < player[i]) j = i;
	cout << "player " << j << " won!!" << endl;
	money[j] += game_money;
}

void Game::show()
{
	cout << "Game money : $" << game_money << ", Bet : " << call_money << endl;
	for(int i=0; i<player_count; i++) {
		if(status[i] == DIE) cout << "D ";
		if(first_to_go == i) cout << "F ";
		if(status[i] != BROKE) {
			cout << "player" << i << "($" << money[i] << ") : ";
			player[i].show(i);
		}
	}
}

void Game::dealer(bool open)
{
	for(int i=0; i<7; i++) {
		if(status[i] == BET || status[i] == CALL) 
			player[i] += deck.distribute_card(open);
	}
}

bool Game::bet(int pl, int mo)
{
	if(mo > 0 && mo <= game_money/2 && bet_count[pl] < 2) {
		bet_count[pl]++;
		call_money += mo;
		money[pl] -= mo;
		game_money += mo;
		status[pl] = BET;
		cout << "player " << pl << " betted " << mo << endl;
		return true;
	} else {
		call(pl);
		return false;
	}
}

void Game::call(int pl)
{
	money[pl] -= call_money;
	game_money += call_money;
	status[pl] = CALL;
	cout << "player " << pl << " called " << call_money << endl;
}

void Game::die(int pl)
{
	status[pl] = DIE;
	cout << " player " << pl << " has died." << endl;
}

void Game::think(int k)
{
	cout << "player " << k << " thinking..." << endl;
	float pt = player[k].predict(deck.deck);
	float p[7] {};
	for(int i=0; i<player_count; i++) {
		if(status[i] != DIE && i != k) 
			p[i] = player[k].predict(deck.deck, player[i].face());
	}
	int nth = count_if(p, p+7, [pt](float a) { return a > pt;});
	switch(nth) {
		case 0: bet(k, game_money/3); break;
		case 1: call(k); break;
		case 2: die(k);
	}
}

void Game::human(int k)
{
	cout << "Raise, Call, Die?";
	char c;
	cin >> c;
	switch(c) {
		case 'r': 
			cout << "How much do you want to bet?($1 ~ $";
			cout << game_money/2 << ")?";
			int m; cin >> m; bet(k, m); break;
		case 'c': call(k); break;
		case 'd': die(k);
	}
}
