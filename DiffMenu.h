#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

//Klasa do stopnia trudnosci. Diff-difficulty
class DiffMenu
{
public:
    DiffMenu(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelected() const { return selected; }

private:
    int selected;
    sf::Font font;
    std::vector<sf::Text> options;
};

