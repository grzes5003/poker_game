#pragma once
#include <vector>
#include "table.h"

class Player
{
	std::pair<Card, Card> karty;
	//zapisuj sb swoje karty jak chcesz
public:
	virtual int odzywka( Table stol ); //-1=pass,0=call,jakas kwota=raise;
	void zobaczKarty(std::pair<Card,Card> para); //gracz daje reqesta do managera, a ten uzywa tej funkcji by zobaczyc karty;
	Player();
	virtual void przedstawSie();
	virtual ~Player();
};

