#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

class Game
{
private:
    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;

    Paddle m_paletka;
    Ball m_pilka;
    std::vector<Brick> m_bloki;

    // prywatne metody klasy
    void processEvents();
    void update(float dt);
    void render();
    void initLevel();   // generowanie bloków

public:
    Game();
    void run();
};
