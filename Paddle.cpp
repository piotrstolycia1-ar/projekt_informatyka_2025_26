#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"

//definicja konstruktora - (ustawia nam on poczatkowe wartosci dla danego obiektu). Konstruktor to moment, w którym obiekt rodzi siê w grze — nadajesz mu rozmiar, kolor, pozycjê i prêdkoœæ, czyli wszystko, co jest mu potrzebne, ¿eby dzia³aæ od pierwszej klatki.
Paddle::Paddle(sf::Vector2f startPoz, sf::Vector2f rozmiar, sf::Vector2f startowaV0)
{
	predkosc = startowaV0;
	ksztalt.setPosition(startPoz);
	ksztalt.setSize(rozmiar);
	ksztalt.setFillColor(sf::Color::Yellow);
	ksztalt.setOrigin(rozmiar.x / 2.f, rozmiar.y / 2.f);  //ustawia srodek geom. obiektu, domyslnie jest (0,0) lewy dolny rog obiektu, tu w srodku szerokosc/2 i wysokosc/2
}


//metoda odpowiadajaca za narysowanie paletki w oknie SFML
void Paddle::draw(sf::RenderTarget& window)
{
	window.draw(ksztalt);
}

void Paddle::ruch(sf::Vector2f windowWidth, float dt)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) && (ksztalt.getPosition().x > ksztalt.getSize().x / 2.f))
	{
		ksztalt.move(-predkosc.x * dt, 0.f);
	}
	else
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && (ksztalt.getPosition().x < windowWidth.x - ksztalt.getSize().x / 2.f))
		{
			ksztalt.move(predkosc.x * dt, 0.f);
		}

}


