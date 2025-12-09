#include "LevelManager.h"

void LevelManager::createBasicLevel(
    std::vector<Brick>& bloki,
    float& blockSizeX,
    float& blockSizeY,
    int windowWidth
)
{
    bloki.clear();

    //ustalenie wartosci poziomu
    const int ILOSC_KOLUMN = 8;
    const int ILOSC_WIERSZY = 4;

    blockSizeX = (windowWidth - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    blockSizeY = 20.f;

    //procedura rysujaca bloki
    for (int y = 0; y < ILOSC_WIERSZY; y++)
    {
        for (int x = 0; x < ILOSC_KOLUMN; x++)
        {
            float posX = x * (blockSizeX + 2.f) + blockSizeX / 2.f;
            float posY = y * (blockSizeY + 2.f) + 50.f;

            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1; //kolor/HP w zaleznosci od rzedu

            bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(blockSizeX, blockSizeY),
                L
            );
        }
    }
}
