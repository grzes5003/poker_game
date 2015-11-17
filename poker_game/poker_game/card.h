#pragma once
#include <utility>
#include <iostream>

class Card
{
	bool isVisible;
	
public:
	enum Kolor{Pik = 0,Kier = 1,Trefl = 2,Karo = 3};
	enum Figura { As = 0, Dwa = 2, Trzy = 3, Cztery = 4, Piec = 5, Szesc = 6, Siedem = 7, Osiem = 8, Dziewiec = 9, Dziesiec = 10, Walet = 11, Dama = 12, Krol = 13 };
	
	Card(Kolor _kolor,Figura _figura);
	std::pair<Kolor, Figura> wartosc();
	virtual ~Card();
private:
	const Kolor kolor;
	const Figura figura;
};

