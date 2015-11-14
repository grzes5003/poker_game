#pragma once
#include "card.h"
#include "player.h"
#include <vector>

class Table
{
public:
	struct player_cards{
		Card card1;
		Card card2;
	};
	int bank; //ile piniendzy na stole doslownie
	int pool; //nie ile hajsu ale na ile licytowac
	std::vector<Card> cardsOnTable;
	std::vector<Player,std::vector<player_cards,int>> playersInGame; //player, jeo karty, hajsy w licytacji

	Table();
	virtual ~Table();
};

