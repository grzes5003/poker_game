#pragma once
#include <vector>
#include "card.h"

class Player
{
public:
	int odzywka(); //-1=pass,0=call,jakas kwota=raise;
	void zobaczKarty(); //gracz daje reqesta do managera, a ten uzywa tej funkcji by zobaczyc karty;
	Player();
	virtual ~Player();
};

