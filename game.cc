#include"game.h"

Game::Game(int many)
{
	player = new Hand[many];
	player_count = many;
}

Game::~Game()
{
	delete [] player;
}

int Game::init_game()
{
	deck.shuffle_deck();
	game_money = 0;
	call_money = 0;
	bet_count = {};
	for(int i=0; i<7; i++) die[i] = false;
	for(int i=0; i<player_count; i++) player[i] += deck.distribute_card(true);
	for(int i=0; i<player_count; i++) player[i] += deck.distribute_card(false);
	for(int i=0; i<player_count; i++) player[i] += deck.distribute_card(false);
}

int Game::decide_first()
{
	int j = 0;
	for(int i=1; i<player_count; i++) if(player[j] < player[i]) j = i;
	return j;
}

int Game::round()
{
	int fr = decide_first();
	int k;
	for(int n = fr; n < fr + player_count; n++) {
		k = n % player_count;
		if(die[k]) continue;
		if(k == 0) {
			cout << "Raise, Call, Die?";
			char c;
			cin >> c;
			switch(c) {
			case 'r': 
				cout << "How much do you want to bet?($1 ~ $";
				cout << game_money/2 << ")?";
				int m;
				cin >> m;
				if(m > 0 && m <= game_money/2 && bet_count[k] < 2) {
					game_money += m;
					call_money += m;
					money[k] -= m;
					bet_count[k]++;
				}
				break;
			case 'c':
				money[k] -= call_money;
				game_money += call_money;
				break;

			case 'd': die[k] = true;
			}
		} else {
			float pt = player[k].predict(deck);
			float p[7] {};
			for(int i=0; i<player_count; i++) {
				if(!die[i] && i != k) 
					p[i] = player[k].predict(deck, player[i].face());
			}
			int nth = count(p, p+7, [](float a) { return a > pt;});
			switch(nth) {
			case 0: 
			}
		
		}
	}
}

Game::bet(int player, int money);
