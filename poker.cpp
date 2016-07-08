#include<iostream>
#include"game.h"
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 2) {
		cout << "usage : " << argv[0] << " [number of players]" << endl;
		return 0;
	}
	Game game(atoi(argv[1]));
	while(game.init_game()) while(game.round() < 8);
}


