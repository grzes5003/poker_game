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

GameManager::GameManager( std::vector<Player> _playerList, int _minpool )  {
	begginer_index = 0;
	stol.minpool = _minpool;
	Gracz gracz = {};
	for( unsigned int i = 0; i < _playerList.size(); i++ ) {
		gracz.karty = std::vector<Card>();
		gracz.money = 100;
		gracz.player = _playerList.at( i );
		gracz.stan = Gra;
		playerList.push_back(gracz);
	}
		
	

	//karty_generate;
	for( unsigned int i = 0; i < 4; i++ ) {
		for( unsigned int x = 0; x < 14; x++ ) {
			cardsList.push_back( Card( Card::Kolor(i), Card::Figura(x) ) );
		}
	}

}

void GameManager::reset() {
	for( unsigned int i = 0; i < 4; i++ ) {
		for( unsigned int x = 0; x < 14; x++ ) {
			cardsList.push_back( Card( Card::Kolor( i ), Card::Figura( x ) ) );
		}
	}
	stol.reset();
	for( unsigned int i = 0; i < playerList.size(); i++ ) {
		playerList.at( i ).karty.clear();
	}
}

void GameManager::rozdanie() {

	//Tasowanie
	for( int i = 0; i<100000; ++i ) {
		int index1 = rand() % cardsList.size();
		int index2 = rand() % cardsList.size();
		std::swap( cardsList.at(index1), cardsList.at(index2) );
	}

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

	reset();
	wybierzZaczynajacego();
}

void GameManager::play() {
	int ile_rozdan = 0;

	while( grajacych( 1 ).size() > 1 ) {
		if( ile_rozdan == 3 ) {
			stol.minpool *= 2;
		}
		rozdanie();
		ile_rozdan++;
	}

	for( unsigned int i = 0; i < playerList.size(); i++ ) {
		std::cout << "Gracz: ";
		playerList.at( i ).player.przedstawSie();
		std::cout << " wygral " << playerList.at( i ).wygrane << " i koncowo ";
		if( playerList.at( i ).stan == Niegra ) {
			std::cout << "WYGRAL STARCIE!!!XD" << std::endl;
		}
		else {
			std::cout << " przegral gre :((" << std::endl;
		}
	}
	
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
			pgracze = &grajacych(0);
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
		pgracze = &grajacych(0);
		for( unsigned int i = 0; i < pgracze->size(); i++ ) {
			zmienWlasnosci( i, pgracze->at( i ).player.odzywka( stol ) );
		}
	}
	
	if( stol.cardsOnTable.size() == 5 ) {
		Gracz *gracz_ptr = &whoWon();
		std::cout << "Wygral gracz ";
		gracz_ptr->player.przedstawSie();
		std::cout << " jego bilans " << gracz_ptr->money << std::endl << std::endl;
		gracz_ptr->wygrane++;

			//metoda wskazuje tego dobrego a reszte pasuje;
	}
}

std::vector<GameManager::Gracz> GameManager::grajacych(unsigned int m) { //jesli 0 - sprawdza pasowanych i nie grajacych, jesli 1 sprawdza nie grajacych, 
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
GameManager::Gracz& GameManager::whoWon() {
	struct Kandydat {
		Gracz* gracz;
		int score;
	};
	std::vector<Kandydat> kandydat_tab;
	std::vector<Gracz> gracz_tab = grajacych( 0 );
	
	unsigned int pomoc1; unsigned int pomoc2;
	std::vector<Card::Figura> karta;
	for( unsigned int i = 0; i < stol.cardsOnTable.size(); i++ ) {
		karta.push_back( stol.cardsOnTable.at( i ).wartosc().second );
	}

	for( unsigned int i = 0; i < gracz_tab.size(); i++) {

		pomoc1 = gracz_tab.at( i ).karty.at( 0 ).wartosc().second;
		pomoc2 = gracz_tab.at( i ).karty.at( 1 ).wartosc().second;

		std::vector<Card> cale_karty; cale_karty.reserve( stol.cardsOnTable.size() + gracz_tab.at( i ).karty.size() );
		cale_karty.insert( cale_karty.end(), stol.cardsOnTable.begin(), stol.cardsOnTable.end() );
		cale_karty.insert( cale_karty.end(), gracz_tab.begin(), gracz_tab.end() );

		std::vector<Card::Figura> fCale_karty; 
		for( unsigned int i = 0; i < cale_karty.size(); i++ ) {
			fCale_karty.push_back( cale_karty.at( i ).wartosc().second );
		}
		
		por::fsort( fCale_karty );
		por::csort( cale_karty );
		//if poker krolewski
		if( isFigura( Card::Figura::As, fCale_karty ) &&
			isFigura( Card::Figura::Krol, fCale_karty ) &&
			isFigura( Card::Figura::Dama, fCale_karty ) &&
			isFigura( Card::Figura::Walet, fCale_karty ) &&
			isFigura( Card::Figura::Dziesiec, fCale_karty ) ) {
			if( cale_karty.at( cale_karty.size() - 1 ).wartosc().first == cale_karty.at( cale_karty.size() - 2 ).wartosc().first &&
				cale_karty.at( cale_karty.size() - 2 ).wartosc().first == cale_karty.at( cale_karty.size() - 3 ).wartosc().first &&
				cale_karty.at( cale_karty.size() - 3 ).wartosc().first == cale_karty.at( cale_karty.size() - 4 ).wartosc().first &&
				cale_karty.at( cale_karty.size() - 4 ).wartosc().first == cale_karty.at( cale_karty.size() - 5 ).wartosc().first &&
				cale_karty.at( cale_karty.size() - 5 ).wartosc().first == cale_karty.at( cale_karty.size() - 6 ).wartosc().first
				) {
				kandydat_tab.at( i ).score = 22;
			}
		}
		//if kareta
		else if( por::ileTychSamych( cale_karty ).second == 4 ) {
			kandydat_tab.at( i ).score = 21; //nwm ile - zgadywanka
		}
		//if full
		else if( por::ileTychSamych( cale_karty ).second == 3 ) {
			if( por::ileTychSamych_bez( cale_karty, Card::Figura( por::ileTychSamych( cale_karty ).first ) ).second == 2 ) {
				kandydat_tab.at( i ).score = 20; //ponownie zgadywanka
			}
		}
		//if kolor

		//if strit

		//if trojka
		else if( por::ileTychSamych( cale_karty ).second == 3 ) {
			kandydat_tab.at( i ).score = 17;
		}
		//if dwie pary
		else if( por::ileTychSamych( cale_karty ).second == 2 ) {
			if( por::ileTychSamych_bez( cale_karty, Card::Figura( por::ileTychSamych( cale_karty ).first ) ).second == 2 )
				kandydat_tab.at( i ).score = 16;
		}
		//if para
		else if( por::ileTychSamych( cale_karty ).second == 2 )
			kandydat_tab.at( i ).score = 15;
		//if ma tlk mocna figure;
		
		else if( por::maxV( karta ) > (pomoc1 > pomoc2) ? pomoc1 : pomoc2 ) {
			pomoc2 = por::maxV( karta );
			kandydat_tab.at( i ).score = static_cast<Card::Figura>(pomoc2);
		}
		else {
			//lol nie dostal
			kandydat_tab.at( i ).score = 0;
		}
		//
	}
	std::vector<int> tab;
	for( unsigned int i = 0; i < kandydat_tab.size(); i++ ) {
		tab.push_back( kandydat_tab.at( i ).score );
	}
	por::ksort<Kandydat>( kandydat_tab, tab );
	return *kandydat_tab.at( kandydat_tab.size() - 1 ).gracz;
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
	bool ma_karty;
	for( int i = 0; i < playerList.size(); i++ ) {
		if( !playerList.at( i ).karty.empty() )
			ma_karty = true;
		else
			ma_karty = false;
	}
	if( ma_karty ) {
		switch( stol.cardsOnTable.size() ) {
		case 0:
			stol.cardsOnTable.push_back( cardsList.at( 0 ) );
			stol.cardsOnTable.push_back( cardsList.at( 1 ) );
			stol.cardsOnTable.push_back( cardsList.at( 2 ) );
			break;
		case 3:
			stol.cardsOnTable.push_back( cardsList.at( 3 ) );
			stol.cardsOnTable.push_back( cardsList.at( 4 ) );
			break;
		}
	}
	else if(!ma_karty ) {
		for( int i = 5; i < playerList.size() + 5; i++) {
			playerList.at( i ).karty.push_back( cardsList.at( i ) );
			playerList.at( i ).karty.push_back( cardsList.at( i + playerList.size() ));
		}
	}
}

bool GameManager::isFigura( Card::Figura jaka, std::vector<Card::Figura> gdzie ) {
	for( unsigned int i = 0; i < gdzie.size(); i++ ) {
		if( gdzie.at( i ) == jaka )
			return true;
	}
	return false;
}

GameManager::~GameManager() {
}
