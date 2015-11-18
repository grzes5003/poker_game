#pragma once
#include "card.h"
#include <vector>

class Table
{
public:
	

	int bank; //ile piniendzy na stole doslownie
	int pool; //nie ile hajsu ale na ile licytowac
	int minpool; //minimalna kwota licytacji
	std::vector<Card> cardsOnTable;
	
	void reset();

	Table(int _minpool);
	Table();
	virtual ~Table();
};

//std::vector<Player, std::vector<player_cards, int>> playersInGame; //player, jeo karty, hajsy w licytacji