#pragma once
#include <utility>
#include <iostream>

class Card
{	
public:
	enum Kolor{Pik = 0,Kier = 1,Trefl = 2,Karo = 3};
	enum Figura { Dwa = 1, Trzy = 2, Cztery = 3, Piec = 4, Szesc = 5, Siedem = 6, Osiem = 7, Dziewiec = 8, Dziesiec = 9, Walet = 10, Dama = 11, Krol = 12, As = 13 };
	
	Card( Kolor _kolor, Figura _figura );
	Card();
	std::pair<Kolor, Figura> wartosc();
	virtual ~Card();
	bool operator==( const Card &a) const;
	bool operator==( const Figura &a ) const;
	
	Card &operator=( const Card& );
private:
	const Kolor kolor;
	const Figura figura;
};

