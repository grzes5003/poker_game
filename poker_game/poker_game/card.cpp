#include "card.h"

Card::Card( Kolor _kolor, Figura _figura ) : kolor(_kolor), figura(_figura) {

}

Card::Card() : kolor(Pik), figura(As) {
}

std::pair<Card::Kolor, Card::Figura> Card::wartosc() {
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
