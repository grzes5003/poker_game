#pragma once
#include "table.h"
#include "player.h"
#include <algorithm>
#include <array>

namespace por {

	std::pair<int,int> ileTychSamych( std::vector<Card> tab ) {
		//pierwszy - co?
		//drugi:
		//if null = 0; if jedna = 1; if 2 = 2; itp 
		//if ten sam kolor i ile -> na minusie ta liczba
		int co; int ile;
		for( unsigned int i = 13; i > 0; i-- ) {
			if( std::count( tab.begin(), tab.end(), Card::Figura(i) ) == 1 ) {
				co = i; ile = 1;
			}
			else if( std::count( tab.begin(), tab.end(), Card::Figura(i) ) == 0 ) {
				co = i; ile = 0;
			}
			if( std::count( tab.begin(), tab.end(), Card::Figura(i) ) == 4 ) {
				co = i; ile = 4;
				break;
			}
			else if( std::count( tab.begin(), tab.end(), Card::Figura(i) ) == 3 ) {
				co = i; ile = 3;
				break;
			}
			else if( std::count( tab.begin(), tab.end(), Card::Figura(i) ) == 2 ) {
				co = i; ile = 2;
				break;
			}
		}
		return std::pair<int, int>( co, ile );
	}
	
	std::pair<int, int> ileTychSamych_bez( std::vector<Card> tab, Card::Figura bez_czego ) {
		//pierwszy - co?
		//drugi:
		//if null = 0; if jedna = 1; if 2 = 2; itp 
		//if ten sam kolor i ile -> na minusie ta liczba
		int co; int ile;
		for( unsigned int i = 13; i > 0; i-- ) {
			if( i != static_cast<Card::Figura>(bez_czego) ) {
				if( std::count( tab.begin(), tab.end(), Card::Figura(i) ) == 1 ) {
					co = i; ile = 1;
				}
				else if( std::count( tab.begin(), tab.end(), Card::Figura(i) ) == 0 ) {
					co = i; ile = 0;
				}
				if( std::count( tab.begin(), tab.end(), Card::Figura(i) ) == 4 ) {
					co = i; ile = 4;
					break;
				}
				else if( std::count( tab.begin(), tab.end(), Card::Figura(i) ) == 3 ) {
					co = i; ile = 3;
					break;
				}
				else if( std::count( tab.begin(), tab.end(), Card::Figura(i) ) == 2 ) {
					co = i; ile = 2;
					break;
				}
			}
		}
		return std::pair<int, int>( co, ile );
	}
	
	Card::Figura maxV( std::vector<Card::Figura> gdzie ) { //POWINNO DZIALAC
		for( unsigned int i = 0; i < gdzie.size() - 1; i++ ) {
			if( gdzie.at( i ) > gdzie.at( i + 1 ) ) {
				std::swap( gdzie.at( i ), gdzie.at( i + 1 ) );
			}
		}
		return gdzie.at( gdzie.size() + 1 );
	}

	std::vector<Card::Figura> fsort( std::vector<Card::Figura> &gdzie ) {
		for( unsigned int i = 0; i < gdzie.size() - 1; i++ ) {
			if( gdzie.at( i ) > gdzie.at( i + 1 ) ) {
				std::swap( gdzie.at( i ), gdzie.at( i + 1 ) );
			}
		}
		return gdzie;
	}

	std::vector<Card> csort( std::vector<Card>& gdzie ) {
		for( unsigned int i = 0; i < gdzie.size() - 1; i++ ) {
			if( gdzie.at( i ).wartosc().second > gdzie.at( i + 1 ).wartosc().second ) {
				std::swap( gdzie.at( i ), gdzie.at( i + 1 ) );
			}
		}
		return gdzie;
	}

	template<class T> //t kandydat
	T ksort( std::vector<T> &gdzie, std::vector<int> tab){
		
		for( unsigned int i = 0; i < gdzie.size()-1; i++ ) {
			if( tab.at( i ) > tab.at( i + 1 ) ) {
				std::swap( gdzie.at( i ), gdzie.at( i + 1 ) );
			}
		}
		return gdzie.at( gdzie.size()-1 );
	}
}

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
	
	std::vector<Gracz> playerList; 
	std::vector<Card> cardsList;
	
	void reset();
	void rozdanie(); //jedna runda
	void runda( int zaczyna );
	std::vector<Gracz> grajacych(unsigned int m );
	Gracz &whoWon();
	void wybierzZaczynajacego(); //wybierz z grajacych!!!
	void rozdajKarty();
	bool isFigura( Card::Figura jaka, std::vector<Card::Figura> gdzie );
public:
	GameManager( std::vector<Player> _playerList, int minpool );
	void play(); //ogolna metoda grajaca

	virtual ~GameManager();
};

