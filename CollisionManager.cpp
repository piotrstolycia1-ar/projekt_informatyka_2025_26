#include "CollisionManager.h"

void CollisionManager::handleBallBrickCollision
(
    Ball& pilka,
    std::vector<Brick>& bloki,
    int& score,
    sf::Text& scoreText
)

{
    //kolizja pilki z blokami
    sf::FloatRect pilkaBounds(
        pilka.gettPosition().x - pilka.getRadius(),
        pilka.gettPosition().y - pilka.getRadius(),
        pilka.getRadius() * 2,
        pilka.getRadius() * 2
    );

    //Iteracja po wszystkich blokach, sprawdza kolizje z pilka 
    for (auto& blk : bloki)
    {
        if (!blk.czyZniszczony())
        {
            if (blk.getGlobalBounds().intersects(pilkaBounds))
            {
                blk.trafienie();

                //nalicz punkty jesli blok faktycznie zosta³ zniszczony
                if (blk.czyZniszczony())
                {
                    //ustawinie ile pkt naliczyc za zbicie klocka
                    score += 15;
                    scoreText.setString("Punkty: " + std::to_string(score));
                }

                //odbicie pilki
                pilka.odbicieY();
                break;
            }
        }
    }
}
