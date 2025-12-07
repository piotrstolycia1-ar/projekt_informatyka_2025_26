#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

//tworze ta strukture pomocnicza co w poleceniu, zapisuje dane klocka w stanie gry
struct BlockData
{
    float x, y;
    int hp;
};

class gameState
{
    private:
        sf::Vector2f paddlePosition; //wektory polozenia(pozycji) paletki, nizej pilka
        sf::Vector2f ballPosition;
        sf::Vector2f ballVelocity; //wektor predkosci pilki
        std::vector<BlockData> blocks; //liczba stanow wszystkich blokow

        int score; //do punktow

    public:
        //BRAK konstruktora
        //metoda capture przyjmujaca referencje do biezacych elementow gry
        void capture(const Paddle&, const Ball&, const std::vector<Brick>&, int currentScore);

        //tu sa gettery
        const sf::Vector2f getPaddlePoz() const
        {
            return paddlePosition;
        }

        const sf::Vector2f getBallPoz() const
        {
            return ballPosition;
        }

        const sf::Vector2f getBallVel() const
        {
            return ballVelocity;
        }

        const std::vector<BlockData>& getBlocks() const  //wykorzystanie struktury pomocniczej
        {
            return blocks;
        }

        //dwie metody zapis do pliku, wczytanie stanu gry z pliku
        bool saveToFile(const std::string& filename) const;

        bool loadFromFile(const std::string& filename);
        void apply(Paddle& paddle, Ball& ball, std::vector<Brick>& blocksOut, float blockW, float blockH);

        int getScore() const { return score; }
        void setScore(int s) { score = s; }

};