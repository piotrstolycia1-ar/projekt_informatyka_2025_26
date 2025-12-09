#pragma once
#include <SFML/Graphics.hpp>

class GameOverManager
{
public:
    static bool checkGameOver(
        float ballY,
        float ballRadius,
        int score,
        sf::Text& scoreAfterDeathText,
        sf::Text& gameOverText,
        sf::RenderWindow& window
    );
};