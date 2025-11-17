#pragma once
#include <SFML/Graphics.hpp>
#include <array> //prosta tablica stalego rozmiaru
#include <iostream>
#include "Brick.h"


Brick::Brick(sf::Vector2f startPoz, sf::Vector2f rozmiar, int L)
{
	punktyZycia = L;
	jestZniszczony = false; //nie jest zniszczony
	setPosition(startPoz);
	setSize(rozmiar);
	setOrigin(rozmiar.x / 2, rozmiar.y / 2);
	aktualizujKolor();

}

const std::array<sf::Color, 4> Brick::colorLUT = {
	sf::Color::Transparent,
	sf::Color::Yellow,
	sf::Color::Magenta,
	sf::Color::Red,
};

void Brick::trafienie()
{
	if (jestZniszczony)
		return; //zakonczenie funkcji
	punktyZycia--;

	if (punktyZycia <= 0)
	{
		jestZniszczony = true; //jest zniszczony
		return;
	}

	aktualizujKolor();
}


void Brick::aktualizujKolor()
{
	if (punktyZycia >= 0 && punktyZycia <= 3)
		this->setFillColor(colorLUT[punktyZycia]);
}

void Brick::draw(sf::RenderTarget& window)
{
	if (!jestZniszczony)
		window.draw(*this);
}

