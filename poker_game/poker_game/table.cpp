#include "table.h"



void Table::reset() {
	bank = 0;
	cardsOnTable.clear();
	pool = 0;
}

Table::Table( int _minpool ) : minpool(_minpool){
}

Table::Table() {
}


Table::~Table() {
}
