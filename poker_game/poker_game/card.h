#pragma once
#include <utility>
#include <iostream>

class Card
{
	bool isVisible;
	enum Kolor{Pik,Kier,Trefl,Karo};
	enum Figura { As = 0, Dwa = 2, Trzy = 3, Cztery = 4, Piec = 5, Szesc = 6, Siedem = 7, Osiem = 8, Dziewiec = 9, Dziesiec = 10, Walet = 11, Dama = 12, Krol = 13 };
	const Kolor kolor;
	const Figura figura;
public:
	Card(Kolor _kolor,Figura _figura);
	std::pair<Kolor, Figura> wartosc();
	virtual ~Card();
};

