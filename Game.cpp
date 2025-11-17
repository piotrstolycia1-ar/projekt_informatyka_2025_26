#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

//refaktoryzacja, zamiana nazw np p1 na m_pilka, pd1 m_paletka

const int SZEROKOSC = 800;
const int WYSOKOSC = 600;

Game::Game()
    : m_window(sf::VideoMode(800, 600), "Gra v.01"),
    m_paletka({ 400.f, 550.f }, { 120.f, 20.f }, { 400.f, 0.f }),
    m_pilka({ 400.f, 250.f }, 20.f, { 300.f, 200.f })
{
    m_window.setFramerateLimit(60);
    initLevel();  
}

void Game::initLevel()
{
    m_bloki.clear(); //zamiana bloki na m_bloki

    //tworzenie blokow stone
    // std::vector<Brick> bloki; //bloki cegly TU BYLO WCZESNIEJ
    //Brick bloki2[10];    NIE MOZNA W TYM STYLU  


    //ustalenie wartosci poziomu
    const int ILOSC_KOLUMN = 8;
    const int ILOSC_WIERSZY = 4;
    float ROZMIAR_BLOKU_X = (SZEROKOSC - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;  //uzaleznic od szerokosci ekranu on ma stalymi
    float ROZMIAR_BLOKU_Y = 20.f;

    //procedura rysujaca bloki
    for (int y = 0; y < ILOSC_WIERSZY; y++)
    {
        for (int x = 0; x < ILOSC_KOLUMN; x++)
        {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f) + ROZMIAR_BLOKU_X / 2.f;
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 50.f;

            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1; //kolor w zaleznosci od rzedu, im nizszy tym slabszy

            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
        }
    }
}

void Game::run()
{
    {
        while (m_window.isOpen())
        {
            float dt = m_deltaClock.restart().asSeconds();

            processEvents();
            update(dt);
            render();
        }
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
}

void Game::update(float dt)
{
    if (m_pilka.gettPosition().y + m_pilka.getRadius() > 595.f) //zapas pieciu pikseli
    {
        cout << "MISS! KONIEC GRY\n";
        sf::sleep(sf::seconds(2));
        m_window.close();   // zamyka okno gry
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
                // odbicie pi³ki
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
}

void Game::render()
{
    m_window.clear(sf::Color::Black); // t³o
    m_pilka.draw(m_window);
    m_paletka.draw(m_window);

    //rysowanie blokow - iterowanie petla
    for (auto& blk : m_bloki)
    {
        blk.draw(m_window);
    }

    m_window.display();
}