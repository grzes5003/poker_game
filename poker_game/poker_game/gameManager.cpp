#include "gameManager.h"



void GameManager::zmienWlasnosci(int index, int odzywka ) {
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
	int numerPrzejscia = 0; //ile bylo przeprowadzonych przejsc - wskazuje czy trza dodac nowe karty
	
	while( grajacych() > 1 ) {
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
	int przejscie = 0;
	if( stol.cardsOnTable.size() == 0 && stol.pool == 0 ) {
		zmienWlasnosci( zaczyna , playerList.at( zaczyna ).player.odzywka( stol ) );
		zaczyna++;
	}
}

int GameManager::grajacych() {
	return 0;
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


GameManager::~GameManager() {
}
