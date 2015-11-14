#pragma once
#include "table.h"
#include <array>

class GameManager
{

	int begginer_index; // index typa ktory ma zaczynac dana licytacje;
	std::vector<Player, std::vector<int, std::array<Card, 2>>> playerlist; //gracz, hajs, jego karty;

public:
	GameManager( std::vector<Player,std::vector<int,std::array<Card,2>>> _playerList );
	void licytacja();

	virtual ~GameManager();
};

