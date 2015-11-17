#include "card.h"

Card::Card( Kolor _kolor, Figura _figura ) : kolor(_kolor), figura(_figura) {
	isVisible = false;
}

std::pair<Card::Kolor, Card::Figura> Card::wartosc() {
	if( !isVisible ) std::cerr << "Error: could not show value if card is not visible";
	else
	return std::pair<Kolor, Figura>(kolor,figura);
}

Card::~Card() {
}

const bool & Card::operator==(const Card & forg ) {
	return (this->wartosc().second == forg.figura) ? true : false;
}
