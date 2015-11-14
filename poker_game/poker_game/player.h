#pragma once
#include "table.h"

class Player
{
public:
	int odzywka(Table stol); //-1=pass,0=call,jakas kwota=raise;
	void zobaczKarty(); //gracz daje reqesta do managera, a ten uzywa tej funkcji by zobaczyc karty;
	Player();
	virtual ~Player();
};

