#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
private:
	//zakotwiczamy w ffigure geom.
	sf::RectangleShape ksztalt;
	sf::Vector2f predkosc{ 200.f, 0.f };  //druga wspolrzedna (y) jest 0 bo paletka tylko w poziomie sie porusza. Vector2f-->wektor dwuwymiarowy, f-od float, ze te parametry (x,y) sa float

public:
	Paddle(sf::Vector2f startPoz, sf::Vector2f rozmiar, sf::Vector2f startowaV0);  //konstruktor, wartosci poczatkowe: pozycja, rozmiar, predkoscV0
	void draw(sf::RenderTarget &window);   //metoda ktora rysuje paletke w oknie
	void ruch(sf::Vector2f windowWidth, float dt);  //metoda odpowiadajaca za sterowanie paletka, prawo lewo

	//Tworzymy tzw gettery, Gettery to okienko na œwiat – pozwalasz innym obiektom zobaczyæ tylko to, co im potrzebne, bez grzebania w œrodku.
	sf::Vector2f gettPosition() 
	{ 
		return ksztalt.getPosition();
	}
	sf::Vector2f gettSize() 
	{
		return ksztalt.getSize();
	}

};



