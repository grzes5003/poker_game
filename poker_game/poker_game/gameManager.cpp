#include "gameManager.h"



void GameManager::zmienWlasnosci(int index, int odzywka ) { //modyfikuje wartosci 
	if( odzywka == -1 )
		playerList.at( index ).stan = Pass;
	else if( odzywka == 0 ) {
		playerList.at( index ).stan = Gra;
		if( playerList.at( index ).money >= stol.pool ) {
			playerList.at( index ).money -= stol.pool;
			stol.bank += stol.pool;
		}
		else {
			stol.bank += playerList.at( index ).money;
			playerList.at( index ).money = 0;
		}
	}
}

GameManager::GameManager( std::vector<Gracz> _playerList ) : playerList(_playerList) {
	begginer_index = 0;
}

void GameManager::rozdanie() {
	//int numerPrzejscia = 0; //ile bylo przeprowadzonych przejsc - wskazuje czy trza dodac nowe karty
	
	while( grajacych().size() > 1 ) {
		runda( begginer_index );
	}

	//znajdz tego jedynego grajacego

	for( unsigned int i = 0; i < playerList.size(); i++ ) {
		if( playerList.at( i ).money == 0 )
			playerList.at(i).stan = Niegra;
	}
	
	wybierzZaczynajacego();
}

void GameManager::play() {
}

void GameManager::runda( int zaczyna ) {
	int zaczyna_pierw = zaczyna;
	if( stol.cardsOnTable.size() == 0 && stol.pool == 0 ) {
		zmienWlasnosci( zaczyna, playerList.at( zaczyna ).player.odzywka( stol ) );
		zaczyna++;
	}
	else if( stol.cardsOnTable.size() == 0 && stol.pool != 0 ) {
		zmienWlasnosci( zaczyna, playerList.at( zaczyna ).player.odzywka( stol ) );
		zaczyna++;
		rozdajKarty(); //rozdaj gracza
		int z = 0; //index tych sprawdzanych od dolu (po przekroczeniu indexow)
		for( int i = 0; i < grajacych().size() - 2; i++ ) {
			if( zaczyna < grajacych().size() - 1 ) {
				zmienWlasnosci( zaczyna, playerList.at( zaczyna ).player.odzywka( stol ) );
				zaczyna++;
			}
			else if( zaczyna >= grajacych().size()-1 ) {
				zmienWlasnosci( z , playerList.at( z ).player.odzywka( stol ) );
				z++;
			}
		}
		rozdajKarty(); //rozdaje na stol pierwsze 3
	}
	if( stol.cardsOnTable.size() == 3 ) {
		for( )
		if( ) {

		}
	}
	if( stol.cardsOnTable.size() == 5 ) {
		whoWon(); //metoda wskazuje tego dobrego a reszte pasuje;
	}
}

std::vector<GameManager::Gracz> GameManager::grajacych() {

	int indeks_osoby_sprawdzanej = 0;
	std::vector<Gracz> players_playing_list;
	while( playerList.size() > indeks_osoby_sprawdzanej ) {
		if( playerList.at( indeks_osoby_sprawdzanej ).stan != 1 ) {
			players_playing_list.push_back( playerList.at( indeks_osoby_sprawdzanej ) );
			indeks_osoby_sprawdzanej++;
		}
		else {
			indeks_osoby_sprawdzanej++;
		}
	}
	return players_playing_list;
}

Player GameManager::whoWon() {
	return Player();
}

void GameManager::wybierzZaczynajacego() {
	if( begginer_index + 1 == playerList.size() - 1 )
		begginer_index = 0;
	if( begginer_index + 1< playerList.size() - 1 )
		begginer_index++;
	if( playerList.at( begginer_index ).stan == Niegra )
		wybierzZaczynajacego();
}

void GameManager::rozdajKarty() {
}


GameManager::~GameManager() {
}
