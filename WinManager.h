#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Brick.h"

class WinManager
{
    public:
    static bool checkWin
    (
        std::vector<Brick>& bloki,
        int score,
        sf::Text& scoreAfterDeathText,
        sf::Text& winText,
        sf::RenderWindow& window
    );
};