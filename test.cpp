#include"player.h"
#include"game.h"
#include<algorithm>
using namespace std;

int main()
{
	Game game(3);
	game.init_game();
	cout << Card::utf8chr(0x23f0) << endl;
	cout << Card::utf8chr(0x231a) << endl;

}
