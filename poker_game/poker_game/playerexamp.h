#pragma once
#include "player.h"
#include <random>
#include <time.h>
class PlayerExamp :
	public virtual Player
{
public:
	PlayerExamp();
	virtual ~PlayerExamp();
	void przedstawSie();
	virtual int odzywka( Table stol );
};

