#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "GameState.h"
#include "Menu.h"
#include "DiffMenu.h"

//refaktoryzacja, zamiana nazw np p1 na m_pilka, pd1 m_paletka itd

const int SZEROKOSC = 800;
const int WYSOKOSC = 600;

Game::Game()
    : m_window(sf::VideoMode(800, 600), "Gra Arkanoid"),
    m_paletka({ 400.f, 550.f }, { 120.f, 20.f }, { 400.f, 0.f }),
    m_pilka({ 400.f, 250.f }, 20.f, { 300.f, 200.f })
{
    m_window.setFramerateLimit(60);
    initLevel();  

    //POD LICZNIK
    m_score = 0;

    //uzywam tej samej czcionki co infoText
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::Yellow);
    m_scoreText.setStyle(sf::Text::Bold);

    m_scoreText.setString("Punkty: 0");

    //ustawienie na prawy gorny rog
    m_scoreText.setPosition(600.f, 10.f);

    //napis GAME OVER
    m_gameOverText.setFont(m_font);
    m_gameOverText.setCharacterSize(72);
    m_gameOverText.setFillColor(sf::Color::Red);
    m_gameOverText.setStyle(sf::Text::Bold);
    m_gameOverText.setString("GAME OVER");
    m_gameOverText.setPosition(170.f, 210.f);

    //punkty pod GAME OVER
    m_scoreAfterDeathText.setFont(m_font);
    m_scoreAfterDeathText.setCharacterSize(32);
    m_scoreAfterDeathText.setFillColor(sf::Color::White);
    m_scoreAfterDeathText.setStyle(sf::Text::Bold);
    m_scoreAfterDeathText.setPosition(250.f, 350.f);

    //tekst WYGRANA
    m_winText.setFont(m_font);
    m_winText.setCharacterSize(72);
    m_winText.setFillColor(sf::Color::Green);
    m_winText.setStyle(sf::Text::Bold);
    m_winText.setString("WYGRANA!");

    //wysrodkowanie tekstu wygrana, w zaleznosci od wlkosci czcionki
    m_winText.setOrigin(
        m_winText.getLocalBounds().width / 2,
        m_winText.getLocalBounds().height / 2
    );
    m_winText.setPosition(400.f, 250.f);
}

void Game::initLevel()
{
    //ladowanie czcionki do napisu informacyjnego
    if (!m_font.loadFromFile("arial.ttf"))
    {
        std::cout << "Blad czcionki info!\n";
    }

    //konfiguracja napisu informacyjnego
    m_infoText.setFont(m_font);
    m_infoText.setCharacterSize(18);
    m_infoText.setFillColor(sf::Color(200, 200, 200));  //jasnoszary
    m_infoText.setString("F5 - Zapis gry        F9 - Wczytaj zapis");
    //ustawienie w dole ekranu
    m_infoText.setPosition(10.f, 570.f);    
    m_bloki.clear(); //zamiana bloki na m_bloki

    //tworzenie blokow stone
    // std::vector<Brick> bloki; //bloki cegly TU BYLO WCZESNIEJ
    //Brick bloki2[10];    NIE MOZNA W TYM STYLU  


    //ustalenie wartosci poziomu
    const int ILOSC_KOLUMN = 8;
    const int ILOSC_WIERSZY = 4;
    m_ROZMIAR_BLOKU_X = (SZEROKOSC - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;  //uzaleznic od szerokosci ekranu on ma stalymi
    m_ROZMIAR_BLOKU_Y = 20.f;

    //procedura rysujaca bloki
    for (int y = 0; y < ILOSC_WIERSZY; y++)
    {
        for (int x = 0; x < ILOSC_KOLUMN; x++)
        {
            float posX = x * (m_ROZMIAR_BLOKU_X + 2.f) + m_ROZMIAR_BLOKU_X / 2.f;
            float posY = y * (m_ROZMIAR_BLOKU_Y + 2.f) + 50.f;

            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1; //kolor w zaleznosci od rzedu, im nizszy tym slabszy

            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(m_ROZMIAR_BLOKU_X, m_ROZMIAR_BLOKU_Y), L);
        }
    }
}

void Game::run()
{
    runMenu();

    if (m_menuSelection == 0)  //nowa gra, jesli wybrano
    {
        //wybor poziomu
        m_difficulty = runDifficultyMenu();

        //utworz poziom
        initLevel();

        //ustawienie poziomu trudnosci, zmienna predkosc
        if (m_difficulty == 1)
            m_pilka.setVelocity({ 220.f, 150.f });
        else if (m_difficulty == 2)
            m_pilka.setVelocity({ 300.f, 200.f });
        else if (m_difficulty == 3)
            m_pilka.setVelocity({ 380.f, 230.f });

        runGameplay();
    }
    else if (m_menuSelection == 1)
    {
        gameState state;
        if (state.loadFromFile("zapis.txt"))
        {
            state.apply(m_paletka, m_pilka, m_bloki,
                m_ROZMIAR_BLOKU_X, m_ROZMIAR_BLOKU_Y);
            runGameplay();
        }
    }
    else if (m_menuSelection == 2)
    {
        showScores();
    }
    else if (m_menuSelection == 3)
    {
        m_window.close();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))  //zamiana na m_window
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }

    //dodanie el. zwiazanego z zapisem
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
    {
        gameState state;
        if (state.loadFromFile("zapis.txt"))
        {
            //przywrócenie paletki
            m_paletka.setPosition(state.getPaddlePoz());

            //przywrócenie pi³ki
            m_pilka.setPosition(state.getBallPoz());
            m_pilka.setVelocity(state.getBallVel());

            //odbudowanie bloków
            m_bloki.clear();
            for (const auto& b : state.getBlocks())
            {
                m_bloki.emplace_back(sf::Vector2f(b.x, b.y),
                    sf::Vector2f(m_ROZMIAR_BLOKU_X, m_ROZMIAR_BLOKU_Y),
                    b.hp);
            }

            std::cout << "Gra wczytana!" << std::endl;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
    {
        gameState state;
        state.capture(m_paletka, m_pilka, m_bloki, m_score);

        if (state.saveToFile("zapis.txt"))
            std::cout << "Zapisano gre!\n";
        else
            std::cout << "Blad podczas zapisu!\n";

        //anty spam
        sf::sleep(sf::milliseconds(200)); 
    }
}

void Game::update(float dt)
{
    if (m_pilka.gettPosition().y + m_pilka.getRadius() > 595.f) //zapas pieciu pikseli
    {
        m_scoreAfterDeathText.setString("Zdobyte punkty: " + std::to_string(m_score));

        //rysowanie ekranu z GAME OVER
        m_window.clear(sf::Color::Black);
        m_window.draw(m_gameOverText);
        m_window.draw(m_scoreAfterDeathText);
        m_window.display();

        sf::sleep(sf::seconds(3));

        //zamkniecie okna gry
        m_window.close();   
    }

    m_paletka.ruch({ SZEROKOSC, WYSOKOSC }, dt);
    m_pilka.ruch({ SZEROKOSC, WYSOKOSC }, m_paletka.gettPosition(), m_paletka.gettSize(), dt);

    //kolizja pilki z blokami
    sf::FloatRect pilkaBounds(
        m_pilka.gettPosition().x - m_pilka.getRadius(),
        m_pilka.gettPosition().y - m_pilka.getRadius(),
        m_pilka.getRadius() * 2,
        m_pilka.getRadius() * 2
    );

    //Iteracja po wszystkich blokach, sprawdza kolizje z pilka 
    for (auto& blk : m_bloki)
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
                    m_score += 15;   
                    m_scoreText.setString("Punkty: " + std::to_string(m_score));
                }

                //odbicie pilki
                m_pilka.odbicieY();
                break;
            }
        }
    }

    /*m_bloki.erase(
        std::remove_if(
            m_bloki.begin(), m_bloki.end(),
            [](const Brick& b) { return b.czyZniszczony(); }
        ),
        m_bloki.end()
    );*/

    //sprawdzanie czy wygrana

    bool allDestroyed = true;
    for (auto& b : m_bloki)
    {
        if (!b.czyZniszczony())
        {
            allDestroyed = false;
            break;
        }
    }

    if (allDestroyed)
    {
        //tekst punktow
        m_scoreAfterDeathText.setString("Zdobyte punkty: " + std::to_string(m_score));
        m_scoreAfterDeathText.setPosition(400.f, 330.f);
        m_scoreAfterDeathText.setOrigin(
            m_scoreAfterDeathText.getLocalBounds().width / 2,
            m_scoreAfterDeathText.getLocalBounds().height / 2
        );

        //wyswietlenie ekranu z WYGRANA
        m_window.clear(sf::Color::Black);
        m_window.draw(m_winText);
        m_window.draw(m_scoreAfterDeathText);
        m_window.display();

        sf::sleep(sf::seconds(3));
        m_window.close();
    }
}

void Game::render()
{
    m_window.clear(sf::Color::Black); 
    m_pilka.draw(m_window);
    m_paletka.draw(m_window);

    //rysowanie blokow, iterowanie petla
    for (auto& blk : m_bloki)
    {
        blk.draw(m_window);
    }
    m_window.draw(m_infoText);
    m_window.draw(m_scoreText);

    m_window.display();
}

void Game::runMenu()
{
    Menu menu(m_window.getSize().x, m_window.getSize().y);
    int selected = -1;

    while (m_window.isOpen() && selected == -1)
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                    menu.przesunG();

                if (event.key.code == sf::Keyboard::Down)
                    menu.przesunD();

                if (event.key.code == sf::Keyboard::Enter)
                {
                    m_menuSelection = menu.getSelectedItem();

                    //wracamy do Game::run()
                    return;   
                }
            }
        }

        m_window.clear();
        menu.draw(m_window);
        m_window.display();
    }
}


void Game::runGameplay()
{
    m_deltaClock.restart();

    while (m_window.isOpen())
    {
        float dt = m_deltaClock.restart().asSeconds();

        processEvents();
        update(dt);
        render();
    }
}

void Game::showScores()
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

    //tworzymy obiekt tekstowy SFML
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

    //petla do wyswietlania wynikow
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                //wyjscie do menu
                return; 
            }
        }

        m_window.clear(sf::Color::Black);
        m_window.draw(wynik);
        m_window.display();
    }
}

int Game::runDifficultyMenu()
{
    DiffMenu menu(m_window.getSize().x, m_window.getSize().y);

    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                    menu.moveUp();

                if (event.key.code == sf::Keyboard::Down)
                    menu.moveDown();

                if (event.key.code == sf::Keyboard::Enter)
                    return menu.getSelected() + 1;  
            }
        }

        m_window.clear();
        menu.draw(m_window);
        m_window.display();
    }

    //domyslnie ustawiamy poziom sredni
    return 2;  
}

