#pragma once
#include "table.h"
#include <array>

class GameManager
{
	enum stanGry { Gra = 1, Pass = 0, Niegra = -1 };
	Table stol;

	struct Gracz {
		Player player;
		int money;
		std::vector<Card> karty;
		stanGry stan;
		int wygrane = 0;
	};

	void zmienWlasnosci(int index, int odzywka);

	int begginer_index; // index typa ktory ma zaczynac dana licytacje;
	
	std::vector<Gracz> playerList; //gracz, hajs, jego karty;
	std::vector<Card> cardsList;
	
	void rozdanie(); //jedna runda
	void runda( int zaczyna );
	std::vector<Gracz> grajacych(unsigned int m );
	Gracz *whoWon();
	void wybierzZaczynajacego(); //wybierz z grajacych!!!
	void rozdajKarty();
public:
	GameManager( std::vector<Gracz> _playerList, int minpool );
	void play(); //ogolna metoda grajaca

	virtual ~GameManager();
};

