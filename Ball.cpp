#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ball.h"

using namespace std;


Ball::Ball(sf::Vector2f startPoz, float promien, sf::Vector2f startowaV0)
{
    predkosc = startowaV0;
    ksztalt.setPosition(startPoz);
    ksztalt.setRadius(promien);
    ksztalt.setFillColor(sf::Color::Yellow);
    ksztalt.setOrigin(sf::Vector2f(promien, promien));
}

void Ball::draw(sf::RenderTarget& window)
{
    window.draw(ksztalt);
}

void Ball::ruch(sf::Vector2f windowSize, sf::Vector2f paddlePos, sf::Vector2f paddleSize, float dt)
{
    //Ruch pi³ki
    ksztalt.move(predkosc * dt);

    //Pobierz pozycjê i promieñ
    sf::Vector2f pos = ksztalt.getPosition();
    float r = ksztalt.getRadius();

    //Odbicie od lewej i prawej œciany
    if (pos.x - r <= 0.f || pos.x + r >= windowSize.x)
    {
        predkosc.x = -predkosc.x; // zmiana kierunku poziomego
    }

    //Odbicie od sufitu
    if (pos.y - r <= 0.f)
    {
        predkosc.y = -predkosc.y; // zmiana kierunku pionowego
    }

    //Kolizja z podloga
    //if (pos.y + r >= windowSize.y)
    //{
       // dla tego gdyby sie miala odbijac od podlogi: predkosc.y = -predkosc.y; // zmiana kierunku pionowego
    //    predkosc = { 0.f, 0.f };
    //}

    //kolizja z paletka
    bool kolizjaPoziomo = (pos.x >= paddlePos.x - paddleSize.x / 2.f && pos.x <= paddlePos.x + paddleSize.x / 2.f);

    bool kolizjaPionowo = (pos.y + r >= paddlePos.y - paddleSize.y / 2.f) && (pos.y - r < paddlePos.y - paddleSize.y / 2.f);

    if (kolizjaPoziomo && kolizjaPionowo)
    {
        predkosc.y = -predkosc.y; // pi³ka leci w górê
        ksztalt.setPosition(pos.x, (paddlePos.y - paddleSize.y / 2.f) - r - 0.1f); // popraw pozycjê, ¿eby siê nie klei³a
        cout << "Punkt!\n";
    }
}

void Ball::odbicieY()
{
    predkosc.y = -predkosc.y;
}
