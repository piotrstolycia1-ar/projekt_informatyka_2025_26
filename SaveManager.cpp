#include "SaveManager.h"
#include <iostream>

void SaveManager::save(
    const Paddle& paddle,
    const Ball& ball,
    const std::vector<Brick>& bloki,
    int score
)
{
    gameState state;
    state.capture(paddle, ball, bloki, score);

    if (state.saveToFile("zapis.txt"))
        std::cout << "Zapisano gre!\n";
    else
        std::cout << "Blad podczas zapisu!\n";
}

bool SaveManager::load(
    Paddle& paddle,
    Ball& ball,
    std::vector<Brick>& bloki,
    float blockSizeX,
    float blockSizeY
)
{
    gameState state;
    if (!state.loadFromFile("zapis.txt"))
        return false;

    paddle.setPosition(state.getPaddlePoz());
    ball.setPosition(state.getBallPoz());
    ball.setVelocity(state.getBallVel());

    bloki.clear();
    for (const auto& b : state.getBlocks())
    {
        bloki.emplace_back(
            sf::Vector2f(b.x, b.y),
            sf::Vector2f(blockSizeX, blockSizeY),
            b.hp
        );
    }

    return true;
}

void SaveManager::showLastSave(sf::RenderWindow& window)
{
    //wczytywanie stanu gry
    gameState state;
    if (!state.loadFromFile("zapis.txt"))
    {
        std::cout << "Brak pliku zapis.txt\n";
        return;
    }

    //tworzenie tekstu do wywwietlenia na ekranie, z zapisem ostatnim
    std::string text = "OSTATNI ZAPIS GRY:\n\n";

    text += "Paletka:  x=" + std::to_string(state.getPaddlePoz().x)
        + "  y=" + std::to_string(state.getPaddlePoz().y) + "\n";

    text += "Pilka:    x=" + std::to_string(state.getBallPoz().x)
        + "  y=" + std::to_string(state.getBallPoz().y) + "\n";

    text += "Predkosc: vx=" + std::to_string(state.getBallVel().x)
        + "  vy=" + std::to_string(state.getBallVel().y) + "\n";

    text += "Wynik: " + std::to_string(state.getScore()) + "\n\n";

    text += "\nBloki: " + std::to_string(state.getBlocks().size()) + "\n";

    for (const auto& b : state.getBlocks())
    {
        text += "x=" + std::to_string(b.x)
            + "  y=" + std::to_string(b.y)
            + "  hp=" + std::to_string(b.hp) + "\n";
    }

    //tworzymy obiekt tekstowy SFML, czyli ta liste z wynikami
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Brak czcionki arial.ttf!\n";
        return;
    }

    sf::Text wynik;
    wynik.setFont(font);
    wynik.setCharacterSize(22);
    wynik.setFillColor(sf::Color::White);
    wynik.setString(text);
    wynik.setPosition(50.f, 40.f);

    //informacja o powrocie do menu
    sf::Text info;
    info.setFont(font);
    info.setCharacterSize(18);
    info.setFillColor(sf::Color::Red);
    info.setString("ESC - powrot do menu");

    //prawy gorny rog
    info.setPosition(window.getSize().x - info.getLocalBounds().width - 20.f,10.f);

    //petla do wyswietlania wynikow
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                //wyjscie do menu
                return;
        }

        window.clear(sf::Color::Black);
        window.draw(wynik);
        window.draw(info); //o powrocie do menu gl
        window.display();
    }
}
