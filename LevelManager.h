#pragma once
#include <vector>
#include "Brick.h"

class LevelManager
{
public:
    static void createBasicLevel(
        std::vector<Brick>& bloki,
        float& blockSizeX,
        float& blockSizeY,
        int windowWidth
    );
};