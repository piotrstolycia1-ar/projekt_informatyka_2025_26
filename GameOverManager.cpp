#include "GameOverManager.h"
#include <string>

bool GameOverManager::checkGameOver(
    float ballY,
    float ballRadius,
    int score,
    sf::Text& scoreAfterDeathText,
    sf::Text& gameOverText,
    sf::RenderWindow& window
)
{
    if (ballY + ballRadius > 595.f) // zapas pieciu pikseli
    {
        scoreAfterDeathText.setString("Zdobyte punkty: " + std::to_string(score));

        //rysowanie ekranu z GAME OVER
        window.clear(sf::Color::Black);
        window.draw(gameOverText);
        window.draw(scoreAfterDeathText);
        window.display();

        sf::sleep(sf::seconds(3));
        window.close();

        return true;
    }

    return false;
}