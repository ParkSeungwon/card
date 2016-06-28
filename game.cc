#include<iostream>
#include<algorithm>
#include"game.h"
#include"player.h"
using namespace std;

Game::Game(int many)
{
	player_count = many;
	for(int i=many; i<7; i++) status[i] = NOT_IN;
	for(int i=0; i<player_count; i++) status[i] = CALL;
	for(int i=0; i<player_count; i++) money[i] = 2000;
}

bool Game::init_game()
{
	int j=0, winner;
	game_money = 0;
	call_money = 0;
	cur_round = 3;
	for(int i=0; i<player_count; i++) {
		if(money[i] <= 0) {
			status[i] = BROKE;
			j++;
		} else {
			winner = i;
			status[i] = CALL;
			player[i].new_game();
			money[i] -= 10;
			game_money += 10;
		}
	}
	if(j == player_count -1) {
		cout << "winner is player " << winner << endl;
		return false;
	}

	deck.shuffle_deck();
	for(int i=0; i<7; i++) bet_count[i] = 0;

	dealer(false);
	dealer(false);
	dealer(true);
	return true;
}

int Game::decide_first()
{
	int j = 0;
	while(status[j] != CALL)  j++;
	for(int i=j+1; i<player_count; i++) {
		if(status[i] != CALL) continue;
		if(player[j] < player[i]) j = i;
	}
	first_to_go = j;
	return j;
}

int Game::round()
{
	int fr = decide_first();
	int k;
	call_money = 0;
	for(int i=0; i<player_count; i++) {
		bet_money[i] = 0;
		bet_count[i] = 0;
		if(status[i] != BROKE && status[i] != DIE) status[i] = BET;
	}
	show();
	for(int n = fr; count(status, status+7, BET) != 0; n++) {
		k = n % player_count;
		if(status[k] == CALL || status[k] == BET) {
			if(k == 0) human(k);
			else think(k);
		}
	}
	cout << endl << "Round " << ++cur_round << endl << endl;
	if(cur_round == 8) open_cards();
	else dealer(true);
	int j = 0, winner;;
	for(int i=0; i<player_count; i++) {
		if(status[i] == DIE || status[i] == BROKE) j++;
		else winner = i;
	}
	if(j == player_count - 1) {
		cur_round = 8;
		money[winner] += game_money;
		cout << "player" << winner << " won!!" << endl;
	}

	return cur_round;
}

void Game::open_cards()
{
	vector<int> v;
	for(int i=0; i<player_count; i++) {
		if(status[i] == CALL) player[i].open_cards();
		v.push_back(i);
	}
	int j = 0;
	for(int i=1; i<v.size(); i++) 
		if(player[v[j]] < player[v[i]]) j = i;
	cout << "player " << v[j] << " won!!" << endl;
	money[j] += game_money;
	for(int i=0; i<player_count; i++) if(money[i] <= 0) status[i] = BROKE;
}

void Game::show()
{
	cout << "Game money : $" << game_money << ", Bet : " << call_money << endl;
	for(int i=0; i<player_count; i++) {
		if(status[i] == DIE) cout << "D ";
		if(first_to_go == i) cout << "F ";
		if(status[i] != BROKE) {
			cout << "player" << i << "($" << money[i] << " - ";
			cout << bet_money[i] << ") : ";
			player[i].show(i);
		}
	}
}

void Game::dealer(bool open)
{
	for(int i=0; i<player_count; i++) {
		if(status[i] == BET || status[i] == CALL) 
			player[i] += deck.distribute_card(open);
	}
}

bool Game::bet(int pl, int mo)
{
	if(mo > call_money-bet_money[pl] && mo<=game_money/2 && bet_count[pl]<2) {
		bet_count[pl]++;
		money[pl] -= mo;
		call_money = bet_money[pl] += mo;
		//call_money = bet_money[pl];
		game_money += mo;
		status[pl] = BET;
		cout << "player " << pl << " betted " << mo << endl;
		show();
		return true;
	} else {
		call(pl);
		return false;
	}
}

void Game::call(int pl)
{
	int diff = call_money - bet_money[pl];
	money[pl] -= diff;
	game_money += diff;
	bet_money[pl] = call_money;
	status[pl] = CALL;
	cout << "player " << pl << " called " << call_money << endl;
	show();
}

void Game::die(int pl)
{
	status[pl] = DIE;
	cout << " player " << pl << " has died." << endl;
}

void Game::think(int k)
{
	cout << "player " << k << " thinking..." << endl;
	auto pt = player[k].predict(deck);
	pair<float, int> p[7] {};
	for(int i=0; i<player_count; i++) {
		if(status[i] != DIE && i != k) 
			p[i] = player[k].predict(deck, player[i]);
	}
	int nth = count_if(p, p+7, [pt](pair<float, int> a) { return a.first > pt.first;});
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

