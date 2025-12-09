#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class HUD
{
	private:
        //do licznika punkotw oraz do informacji
        sf::Font m_font;
        sf::Text m_infoText;
        sf::Text m_scoreText;
        int m_score = 0;

	public:
        //konstruktor
        HUD();

};