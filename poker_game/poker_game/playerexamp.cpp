#include "playerexamp.h"

void PlayerExamp::przedstawSie() {
	std::cout << "jestem ja" << std::endl;
}

int PlayerExamp::odzywka(Table stol) {
	if( stol.cardsOnTable.empty() && stol.pool == 0) {
		return stol.minpool;
	}
	else if(stol.cardsOnTable.empty() && stol.pool != 0){
		return stol.pool++;
	}
	else if( !stol.cardsOnTable.empty() ) {
		srand( time( NULL ) );
		return ((rand() % 2) * (-1));
	}
}

PlayerExamp::PlayerExamp() {
}


PlayerExamp::~PlayerExamp() {
}
