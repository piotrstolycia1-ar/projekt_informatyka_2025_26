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
    int m_menuSelection = -1;

    //prywatne metody klasy
    void processEvents();
    void update(float dt);
    void render();
    void initLevel();   //do generowania blokow
    void runMenu();
    void runGameplay();
    void showScores();

    float m_ROZMIAR_BLOKU_X;
    float m_ROZMIAR_BLOKU_Y;

    //do informacji
    sf::Font m_font;
    sf::Text m_infoText;

    //do licznika punkotw
    int m_score = 0;
    sf::Text m_scoreText;
    sf::Font m_fontScore;

    //do zakonczenia
    sf::Text m_gameOverText;
    sf::Text m_scoreAfterDeathText;

    //do ekranu wygranej
    sf::Text m_winText;

    //pod pozuiom trudnosci
    int runDifficultyMenu();
    int m_difficulty;

public:
    Game();
    void run();
};
