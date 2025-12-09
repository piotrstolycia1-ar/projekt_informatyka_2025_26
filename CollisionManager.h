#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Brick.h"

class CollisionManager
{
public:
    static void handleBallBrickCollision(
        Ball& pilka,
        std::vector<Brick>& bloki,
        int& score,
        sf::Text& scoreText
    );
};
