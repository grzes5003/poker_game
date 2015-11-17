#include "gameManager.h"



void GameManager::zmienWlasnosci(int index, int odzywka ) { //modyfikuje wartosci; -1 pass; 0 rownaj; 0++ konkretna kwota;
	if( stol.pool != 0 ) {
		if( odzywka == -1 )
			playerList.at( index ).stan = Pass;
		else if( odzywka == 0 ) {
			playerList.at( index ).stan = Gra; //NWM CZY DOBRZE ZE TU TO ZMENIAM
			if( playerList.at( index ).money >= stol.pool ) {
				playerList.at( index ).money -= stol.pool;
				stol.bank += stol.pool;
			}
			else {
				stol.bank += playerList.at( index ).money;
				playerList.at( index ).money = 0;
			}
		}
		else if( odzywka > 0 ) {
			if( odzywka >= stol.pool ) {
				playerList.at( index ).money -= odzywka;
				stol.pool = odzywka;
				stol.bank += odzywka;
			}
			else {
				std::cout << "Gracz ";
				playerList.at( index ).player.przedstawSie();
				std::cout << "podaje zla kwote licytacyjna: jest za mala" << std::endl;
				playerList.at( index ).stan = Niegra;
			}
		}
	}
	else {
		if( odzywka >= stol.minpool ) {
			playerList.at( index ).money -= stol.minpool;
			stol.pool = odzywka;
			stol.bank += odzywka;
		}
		else if(odzywka < stol.minpool ) {
			if( playerList.at( index ).money == odzywka ) {
				stol.pool = odzywka;
				stol.bank += odzywka;
			}
			else {
				std::cout << "Zla kwota wejscia w ciemno gracza ";
				playerList.at( index ).player.przedstawSie();
				std::cout << ": kwota zbyt mala a gracz nie gra vabank! Dyskwalifikacja" << std::endl;
				playerList.at( index ).stan = Niegra;
			}
		}
	}
}

GameManager::GameManager( std::vector<Gracz> _playerList ) : playerList(_playerList) {
	begginer_index = 0;
	
	//karty_generate;
	for( unsigned int i = 0; i < 4; i++ ) {
		for( unsigned int x = 0; x < 14; x++ ) {
			cardsList.push_back( Card( static_cast<Card::Kolor>(i), static_cast<Card::Figura>(x) ) );
		}
	}

}

void GameManager::rozdanie() {
	//int numerPrzejscia = 0; //ile bylo przeprowadzonych przejsc - wskazuje czy trza dodac nowe karty
	
	while( grajacych(0).size() > 1 ) {
		runda( begginer_index );
	}

	//znajdz tego jedynego grajacego

	for( unsigned int i = 0; i < playerList.size(); i++ ) {
		if( playerList.at( i ).money <= 0 )
			playerList.at( i ).stan = Niegra;
		else
			playerList.at( i ).stan = Gra;
	}
	
	wybierzZaczynajacego();
}

void GameManager::play() {

}

void GameManager::runda( int zaczyna ) {
	//BEGGINER_INDEX JEST INDEXEM Z GRAJACYCH!
	std::vector<Gracz> *pgracze;
	int zaczyna_pierw = zaczyna;
	if( stol.cardsOnTable.size() == 0 && stol.pool == 0 ) { ///pierwszy ziomek licytuje w ciemno
		zmienWlasnosci( zaczyna, grajacych(0).at( zaczyna ).player.odzywka( stol ) );
		zaczyna++;
	}
	else if( stol.cardsOnTable.size() == 0 && stol.pool != 0 ) { ///drugi ziomek licytuje w ciemno
		zmienWlasnosci( zaczyna, grajacych(0).at( zaczyna ).player.odzywka( stol ) );
		zaczyna++;
		//
		rozdajKarty(); //rozdaj gracza
		//
		int z = 0; //index tych sprawdzanych od dolu (po przekroczeniu indexow)
		if( grajacych(0).size() > 2 ) {
			*pgracze = grajacych(0);
			for( unsigned int i = 0; i < pgracze->size() - 2; i++ ) { ///reszta licytuje w pol ciemno xd
				if( zaczyna < pgracze-> size() ) {
					zmienWlasnosci( zaczyna, pgracze->at( zaczyna ).player.odzywka( stol ) );
					zaczyna++;
				}
				else if( zaczyna >= pgracze->size() - 1 ) {
					zmienWlasnosci( z, pgracze->at( z ).player.odzywka( stol ) );
					z++;
				}
			}
		}
		rozdajKarty(); //rozdaje na stol pierwsze 3
	}
	///licytacja ponownie
	//nwm co jesli jest tlk 2 licytujacych
	if( stol.cardsOnTable.size() == 3 ) {
		*pgracze = grajacych(0);
		for( unsigned int i = 0; i < pgracze->size(); i++ ) {
			zmienWlasnosci( i, pgracze->at( i ).player.odzywka( stol ) );
		}
	}
	if( stol.cardsOnTable.size() == 5 ) {
		whoWon(); //metoda wskazuje tego dobrego a reszte pasuje;
	}
}

std::vector<GameManager::Gracz> GameManager::grajacych(unsigned int m) { //jesli 0 - sprawdza pasowanych i nie grajacych, jesli 1 sprawdza nie grajacych
	int indeks_osoby_sprawdzanej = 0;
	std::vector<Gracz> players_playing_list;
	if( m == 0 ) {
		
		while( playerList.size() > indeks_osoby_sprawdzanej ) {
			if( playerList.at( indeks_osoby_sprawdzanej ).stan != Gra ) {
				players_playing_list.push_back( playerList.at( indeks_osoby_sprawdzanej ) );
				indeks_osoby_sprawdzanej++;
			}
			else {
				indeks_osoby_sprawdzanej++;
			}
		}
		return players_playing_list;
	}
	else if(m == 1){
		
		while( playerList.size() > indeks_osoby_sprawdzanej ) {
			if( playerList.at( indeks_osoby_sprawdzanej ).stan == Niegra ) {
				players_playing_list.push_back( playerList.at( indeks_osoby_sprawdzanej ) );
				indeks_osoby_sprawdzanej++;
			}
			else {
				indeks_osoby_sprawdzanej++;
			}
		}
		return players_playing_list;
	}
	else {
		std::cout << "error: grajacy nie zwraca wartosci: zly arg" << std::endl;
	}
}

//jeszcze mozliwosc ze nikt nie wygral - zostaw hajs na stole;
GameManager::Gracz* GameManager::whoWon() {
	struct Kandydat {
		Gracz* gracz;
		int score;
	};
	std::vector<Kandydat> kandydat_tab;
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
