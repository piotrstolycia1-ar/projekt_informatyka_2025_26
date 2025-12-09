#include "WinManager.h"
#include <string>

bool WinManager::checkWin(
    std::vector<Brick>& bloki,
    int score,
    sf::Text& scoreAfterDeathText,
    sf::Text& winText,
    sf::RenderWindow& window
)
{
    bool allDestroyed = true;
    for (auto& b : bloki)
    {
        if (!b.czyZniszczony())
        {
            allDestroyed = false;
            break;
        }
    }

    //warunek, czy wszystkie klocki zniszczone
    if (allDestroyed)
    {
        //ustawianie tekstu
        scoreAfterDeathText.setString("Zdobyte punkty: " + std::to_string(score));
        scoreAfterDeathText.setPosition(400.f, 330.f);
        scoreAfterDeathText.setOrigin(
            scoreAfterDeathText.getLocalBounds().width / 2,
            scoreAfterDeathText.getLocalBounds().height / 2
        );

        window.clear(sf::Color::Black);
        window.draw(winText); //rysowanie napisu
        window.draw(scoreAfterDeathText);
        window.display();

        sf::sleep(sf::seconds(3));
        window.close();

        return true;
    }

    return false;
}