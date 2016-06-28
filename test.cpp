#include"player.h"
#include"game.h"
#include<algorithm>
using namespace std;

int main()
{
	Game game(3);
	game.init_game();
	for(auto& a : game.player) a.show(2);
	cout << game.decide_first();
	
	game.show();

}
