#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

//W tych managerach nie stosujemy hermetyzacji, bo te klasy nie reprezentuja obiektow, tylko pelnia rolê narzedzi
class SaveManager
{
public:
    static void save(
        const Paddle& paddle,
        const Ball& ball,
        const std::vector<Brick>& bloki,
        int score
    );

    static bool load(
        Paddle& paddle,
        Ball& ball,
        std::vector<Brick>& bloki,
        float blockSizeX,
        float blockSizeY
    );

    static void showLastSave(sf::RenderWindow& window);
};