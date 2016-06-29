#include<map>
#include<random>
#include<algorithm>
#include<iostream>
#include<exception>
#include<string>
#include"card.h"
#include"combi.h"
#include"hand.h"
#include"game.h"
using namespace std;
constexpr const char* Card::glyph[4];
constexpr const char Card::g[4];

int main(int argc, char** argv)
{
	if(argc < 2) {
		cout << "usage : " << argv[0] << " [number of players]" << endl;
		return 0;
	}
	Game game(atoi(argv[1]));
	while(game.init_game()) while(game.round() < 8);
}


