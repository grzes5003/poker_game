#include "card.h"

Card::Card( Kolor _kolor, Figura _figura ) : kolor(_kolor), figura(_figura) {
	isVisible = true;
}

Card::Card() : kolor(Pik), figura(As) {
}

std::pair<Card::Kolor, Card::Figura> Card::wartosc() {
	if( !isVisible ) std::cerr << "Error: could not show value if card is not visible";
	else
	return std::pair<Kolor, Figura>(kolor,figura);
}

Card::~Card() {
}

bool Card::operator==( const Card & a ) const {
	return (this->figura == a.figura)? true : false;
}

bool Card::operator==( const Figura & a ) const {
	return (this->figura == a) ? true : false;
}


Card & Card::operator=( const Card & forg ) {
	return *this;
}
