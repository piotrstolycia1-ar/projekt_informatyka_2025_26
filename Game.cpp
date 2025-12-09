#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "GameState.h"
#include "Menu.h"
#include "DiffMenu.h"
#include "CollisionManager.h"
#include "WinManager.h"
#include "GameOverManager.h"
#include "SaveManager.h"
#include "LevelManager.h"

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

    m_score = 0;//POD LICZNIK

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

    //punkty widoczne pod GAME OVER
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
    m_infoText.setPosition(10.f, 570.f);  //ustawienie w dole ekranu  
    m_bloki.clear(); //zamiana bloki na m_bloki

    //tworzenie blokow stone
    // std::vector<Brick> bloki; //bloki cegly TU BYLO WCZESNIEJ //Brick bloki2[10];    NIE MOZNA W TYM STYLU  
 
    //budowanie poziomu
    LevelManager::createBasicLevel(
        m_bloki,
        m_ROZMIAR_BLOKU_X,
        m_ROZMIAR_BLOKU_Y,
        SZEROKOSC
    );
}

void Game::run()
{
    while (m_window.isOpen())
    {
        Menu menu(m_window.getSize().x, m_window.getSize().y);
        m_menuSelection = menu.run(m_window);

        if (m_menuSelection == 0)  //nowa gra, jesli wybrano
        {
            //wybor poziomu
            DiffMenu diffMenu(m_window.getSize().x, m_window.getSize().y);
            m_difficulty = diffMenu.run(m_window);

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
        else if (m_menuSelection == 1)   //wczytaj gre
        {
            gameState state;
            if (state.loadFromFile("zapis.txt"))
            {
                state.apply(
                    m_paletka,
                    m_pilka,
                    m_bloki,
                    m_ROZMIAR_BLOKU_X,
                    m_ROZMIAR_BLOKU_Y
                );
                runGameplay();
            }
        }
        else if (m_menuSelection == 2)   //wyniki
        {
            showScores();   //po ESC wracamy do menu glownego
        }
        else if (m_menuSelection == 3)   //wyjscie z gry
        {
            m_window.close();
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

    //Wczytanie zapisu przy pomocy F9
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
    {
        SaveManager::load(
            m_paletka,
            m_pilka,
            m_bloki,
            m_ROZMIAR_BLOKU_X,
            m_ROZMIAR_BLOKU_Y
        );
    }

    //do zapisu przy pomocy F5
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
    {
        SaveManager::save(
            m_paletka,
            m_pilka,
            m_bloki,
            m_score
        );
        sf::sleep(sf::milliseconds(200)); // anty spam
    }
}

void Game::update(float dt)
{
    //manager wyswietlania ekranu game over po nieodbiciu
    GameOverManager::checkGameOver(
        m_pilka.gettPosition().y,
        m_pilka.getRadius(),
        m_score,
        m_scoreAfterDeathText,
        m_gameOverText,
        m_window
    );

    m_paletka.ruch({ SZEROKOSC, WYSOKOSC }, dt);
    m_pilka.ruch({ SZEROKOSC, WYSOKOSC }, m_paletka.gettPosition(), m_paletka.gettSize(), dt);

    //manager kolizji pilka–bloki
    CollisionManager::handleBallBrickCollision
    (
        m_pilka,
        m_bloki,
        m_score,
        m_scoreText
    );

    /*m_bloki.erase(
        std::remove_if(
            m_bloki.begin(), m_bloki.end(),
            [](const Brick& b) { return b.czyZniszczony(); }
        ),
        m_bloki.end()
    );*/

    //sprawdzanie wygranej
    WinManager::checkWin(
        m_bloki,
        m_score,
        m_scoreAfterDeathText,
        m_winText,
        m_window
    );
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

//Zapis wynikow na tablicy wynikow
void Game::showScores()
{
    SaveManager::showLastSave(m_window);
}



