#include<iostream>
#include<algorithm>
#include<functional>
#include"game.h"
#include"player.h"
using namespace std;

Game::Game(int many) : dist(0.0, 0.3)
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
	cur_player_count = 0;
	for(int i=0; i<player_count; i++) {
		if(money[i] <= 0) {
			status[i] = BROKE;
			j++;
		} else {
			cur_player_count++;
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

	cout << endl << "---------------New Game started-----------------" << endl;
	dealer(false);
	dealer(false);
	dealer(true);
	return true;
}

int Game::decide_first()
{
	int j = 0;
	while(status[j] == DIE || status[j] == BROKE)  j++;
	for(int i=j+1; i<player_count; i++) {
		if(status[i] != CALL && status[i] != BET) continue;
		if(player[j] < player[i]) j = i;
	}
	first_to_go = j;
	return j;
}

int Game::round()
{
	int fr = decide_first();
	int k;
	call_count = -1;
	call_money = 0;
	for(int i=0; i<player_count; i++) {
		bet_money[i] = 0;
		bet_count[i] = 0;
		if(status[i] != BROKE && status[i] != DIE) status[i] = BET;
		if(status[i] != BROKE) {
			show(i);
			cout << endl;
		}
	}
	cout << endl;
	for(int n = fr; call_count && count(status, status+7, BET) != 0; n++) {
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
	vector<int> v;
	for(int i=0; i<player_count; i++) {
		if(status[i] == BROKE) continue;
		cout << "player " << i << " has ";
		if(status[i] == CALL || status[i] == BET) player[i].open_cards();
		else if(status[i] == DIE) cout << "died.";
		cout << endl;
		v.push_back(i);
	}
	int j = 0;
	for(int i=1; i<v.size(); i++) 
		if(player[v[j]] < player[v[i]]) j = i;
	cout << "player " << v[j] << " won + $" << game_money << endl;
	money[v[j]] += game_money;
	for(int i=0; i<player_count; i++) if(money[i] <= 0) status[i] = BROKE;
}

void Game::show(int pl)
{
	cout << "Deposit : $";
	cout.width(5); cout << right << game_money << ',';
	cout.width(5); cout << right << call_money << " | ";
	if(status[pl] == DIE) cout << Card::utf8chr(0x2620);
	if(first_to_go == pl) cout << Card::utf8chr(0x2691);
	if(status[pl] != BROKE) {
		if(pl == 0) cout << " You";
		else cout << " player" << pl;
		cout << "($" << money[pl] << " - ";
		cout << bet_money[pl] << ") : ";
		player[pl].show(pl);
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
	if(mo > game_money/2) mo = game_money / 2;
	if(mo > 100 + call_money - bet_money[pl]) mo = 100 + call_money - bet_money[pl];
	if(call_count && mo > call_money-bet_money[pl] && bet_count[pl]<2) {
		bet_count[pl]++;
		money[pl] -= mo;
		call_money = bet_money[pl] += mo;
		//call_money = bet_money[pl];
		game_money += mo;
		call_count = cur_player_count - 1;
		status[pl] = BET;
		show(pl);
		cout << " betted " << mo << endl;
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
	call_count--;
	bet_money[pl] = call_money;
	status[pl] = CALL;
	show(pl);
	cout << " called " << call_money << endl;
}

void Game::die(int pl)
{
	status[pl] = DIE;
	show(pl);
	call_count--;
	cur_player_count--;
	cout << " has died." << endl;
	int j = 0, winner;
	for(int i=0; i<player_count; i++) {
		if(status[i] == DIE || status[i] == BROKE) j++;
		else winner = i;
	}
	if(j == player_count - 1) {
		cur_round = 8;
		money[winner] += game_money;
		cout << endl << "player" << winner << " won $" << game_money << endl;
	}
}

void Game::think(int k)
{
	auto pt = player[k].predict(deck);
	pair<float, int> p[7] {};
	for(int i=0; i<player_count; i++) {
		if(status[i] != DIE && status[i] != BROKE && i != k) 
			p[i] = player[k].predict(deck, player[i]);
	}
	sort(p, p+7, greater<pair<float, int>>()); 
	float v = (1 + pt.first - p[0].first) / 3;
	v += dist(rand);
	if(v < 0) {
		if(call_money - bet_money[k] < 30) call(k); 
		else die(k);
	} else if(v < 0.5) call(k);
	else bet(k, (v - 0.5) * game_money);
	//int nth = count_if(p, p+7, [pt](pair<float, int> a) { return a.first > pt.first;});
//	switch(nth) {
//		case 0: bet(k, game_money/3); break;
//		case 1: call(k); break;
//		default: die(k);
//	}
}

void Game::human(int k)
{
	cout << "Raise, Call, Die?";
	char c;
	cin >> c;
	int diff = call_money - bet_money[k];
	switch(c) {
		case 'r': 
			cout << "How much do you want to bet?($";
			cout << diff + 1 << " ~ $";
			cout << (game_money/2 < diff+100 ? game_money/2 : diff+100) <<  ")?";
			int m; cin >> m; bet(k, m); break;
		case 'c': call(k); break;
		case 'd': die(k);
	}
}

