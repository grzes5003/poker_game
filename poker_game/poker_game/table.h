#pragma once
#include "card.h"
#include "player.h"
#include <vector>

class Table
{
protected:
	struct player_cards{
		Card card1;
		Card card2;
	};
	std::vector<Card> cardsOnTable;
	std::vector<Player> playersInGame;
public:
	Table();
	virtual ~Table();
};

