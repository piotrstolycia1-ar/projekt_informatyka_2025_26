#pragma once
#include <SFML/Graphics.hpp>
#include <array> //prosta tablica stalego rozmiaru
#include <iostream>


class Brick : public sf::RectangleShape //dziedziczenie po rectangleShape
{
	private:
		int punktyZycia; //od 0 do 3, gdy 0 to nie istnieje
		bool jestZniszczony; //jesli tak to true(1)
		//sf::RectangleShape brick; nie jest potrzebne, mamy dziedziczenie
		static const std::array<sf::Color, 4> colorLUT; //tablica look-up, potem nic do niej nie bedzie mozna dodawac



	public: 
		Brick(sf::Vector2f startPoz, sf::Vector2f rozmiar, int L); //tworzymy konstruktor, zeby zrobic klocek z danymi parametrami, wartosci dwuelementowe tworze na wektorach
		//L liczba zyc

		//metoda aktualizujaca kolor w zaleznosci od L(liczby zyc)
		void aktualizujKolor();
		void trafienie(); //mechanizm aktualizacji pkt zycia

		//procedura rysujaca
		void draw(sf::RenderTarget &window);

		//getter
		bool czyZniszczony() const
		{ 
			return jestZniszczony;
		}

		//getter podtrzebny do zadania z zapisem, (gameState)
		int getHP() const
		{
			return punktyZycia;
		}

};



