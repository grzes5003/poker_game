#include "gameManager.h"

int main() {
	PlayerExamp player1, player2, player3;
	std::vector<Player*> l = { &player1,&player2,&player3 };
	GameManager gamemanager( l, 20 );
	gamemanager.play();
	char g;
	std::cin >> g;
	return 0;
}