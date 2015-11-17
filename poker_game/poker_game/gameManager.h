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
		std::array<Card, 2> karty;
		stanGry stan;
		int wygrane = 0;
	};

	void zmienWlasnosci(int index, int odzywka);

	int begginer_index; // index typa ktory ma zaczynac dana licytacje;
	std::vector<Gracz> playerList; //gracz, hajs, jego karty;
	std::vector<Card> cardsList;
public:
	GameManager( std::vector<Gracz> _playerList );
	void rozdanie(); //jedna runda
	void play(); //ogolna metoda grajaca
	void runda( int zaczyna );
	std::vector<Gracz> grajacych(unsigned int m );
	Gracz *whoWon();
	void wybierzZaczynajacego(); //wybierz z grajacych!!!
	void rozdajKarty();

	virtual ~GameManager();
};

