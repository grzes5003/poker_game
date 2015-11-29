#pragma once
#include "table.h"

class Player
{
protected:
	std::pair<Card, Card> karty;
	//zapisuj sb swoje karty jak chcesz
public:
	int i;
	virtual int odzywka( Table stol ); //-1=pass,0=call,jakas kwota=raise;
	void zobaczKarty(std::pair<Card,Card> para); //gracz daje reqesta do managera, a ten uzywa tej funkcji by zobaczyc karty;
	Player();
	void przedstawSie();
	virtual ~Player();
};

