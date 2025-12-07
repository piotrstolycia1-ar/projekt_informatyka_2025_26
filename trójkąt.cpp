#include <SFML/Graphics.hpp>

int main()
{
    // Tworzymy okno
    sf::RenderWindow window(sf::VideoMode(400, 400), "Trójk¹t SFML");

    // Tworzymy kszta³t trójk¹ta (3 punkty)
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(200.f, 50.f));   // wierzcho³ek górny
    triangle.setPoint(1, sf::Vector2f(100.f, 300.f));  // lewy dolny
    triangle.setPoint(2, sf::Vector2f(300.f, 300.f));  // prawy dolny

    // Ustawiamy kolor wype³nienia i obramowania
    triangle.setFillColor(sf::Color::Yellow);
    triangle.setOutlineThickness(4);
    triangle.setOutlineColor(sf::Color::Black);

    // G³ówna pêtla programu
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(triangle);
        window.display();
    }

    return 0;
}
