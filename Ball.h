#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Ball
{
private: 
	//zakotwiczamy w figure geom.
	sf::CircleShape ksztalt;
	sf::Vector2f predkosc{ 200.f, 0.f };

public:
	Ball(sf::Vector2f startPoz, float promien, sf::Vector2f startowaV0);
	void draw(sf::RenderTarget &window);
    void ruch(sf::Vector2f windowSize, sf::Vector2f paddlePos, sf::Vector2f paddleSize, float dt);  //paddlePos-pozycja srodka paletki w x i y, moge sie dostac bo to wektor

    //potrzebne metody do zamkniecia okna
    sf::Vector2f gettPosition() const
    {
        return ksztalt.getPosition();
    }
    
    float getRadius() const
    {
        return ksztalt.getRadius();
    }

    //getter pod zapis (gameState)
    sf::Vector2f getVelocity() const
    { 
        return predkosc;
    }

    //pod bricks spesjalnie
    void odbicieY();

    //settery
    void setPosition(const sf::Vector2f& pos)
    {
        ksztalt.setPosition(pos);
    }

    void setVelocity(const sf::Vector2f& vel)
    {
        predkosc = vel;
    }
};


