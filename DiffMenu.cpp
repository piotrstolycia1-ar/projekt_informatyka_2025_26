#include "DiffMenu.h"

DiffMenu::DiffMenu(float width, float height)
{
    font.loadFromFile("arial.ttf");

    std::vector<std::string> labels = {
        "Poziom 1 (Easy)",
        "Poziom 2 (Medium)",
        "Poziom 3 (Hard)"
    };

    for (int i = 0; i < labels.size(); i++)
    {
        sf::Text text;
        text.setFont(font);
        text.setString(labels[i]);
        text.setCharacterSize(36);
        text.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
        text.setPosition(width / 2 - 150, 200 + i * 80);
        options.push_back(text);
    }

    selected = 0;
}

void DiffMenu::draw(sf::RenderWindow& window)
{
    for (auto& t : options)
        window.draw(t);
}

void DiffMenu::moveUp()
{
    options[selected].setFillColor(sf::Color::White);
    selected = (selected - 1 + options.size()) % options.size();
    options[selected].setFillColor(sf::Color::Yellow);
}

void DiffMenu::moveDown()
{
    options[selected].setFillColor(sf::Color::White);
    selected = (selected + 1) % options.size();
    options[selected].setFillColor(sf::Color::Yellow);
}

//przeniesienie funkcjonalnosci z game.cpp
int DiffMenu::run(sf::RenderWindow& window)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                    moveUp();

                if (event.key.code == sf::Keyboard::Down)
                    moveDown();

                if (event.key.code == sf::Keyboard::Enter)
                    return getSelected() + 1; 
            }
        }

        window.clear();
        draw(window);
        window.display();
    }

    // domyœlnie poziom œredni
    return 2;
}