#include "GameState.h"
#include <fstream>
#include <string>

//tutaj dzialanie metody capture, klasy gameState

void gameState::capture(const Paddle& p, const Ball& b, const std::vector<Brick>& bloki, int currentScore) // nazwy lokalne dla metody p b bloki
{
	//pozycja paletki 
	paddlePosition = p.gettPosition(); //z gettera w paddle.h

	//pozycja i wektor prêdkoœci pi³ki
	ballPosition = b.gettPosition();
	ballVelocity = b.getVelocity();

	//zapis bloków
	blocks.clear();  //usuwa cala zawartosc wektora blocks, czysci


    //petla przechodzaca "po wwszystkich blokach", sprawdza czy dany blok nie zniszczony
    for (const auto& blok : bloki)
    {
        if (!blok.czyZniszczony())
        {
            //dla jednego bloku tworzy maluy obiekt (snapshot) z jego danymi i zapisuje go do wektora
            BlockData dane;
            dane.x = blok.getPosition().x;
            dane.y = blok.getPosition().y;
            dane.hp = blok.getHP();
            blocks.push_back(dane);
        }
    }

    score = currentScore;
}


bool gameState::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;

    //zapsywanie do paletki
    file << "PADDLE: " << paddlePosition.x << " " << paddlePosition.y << "\n";

    //zapsywanie do pi³ki
    file << "BALL: "
        << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";

    //liczba bloków
    file << "BLOCKS_COUNT: " << blocks.size() << "\n";

    //zapsywanie do blokow
    for (const auto& b : blocks)
    {
        file << b.x << " " << b.y << " " << b.hp << "\n";
    }

    file << "SCORE " << score << "\n";

    file.close();
    return true;
}


bool gameState::loadFromFile(const std::string& filename)
{
    //sprawdzenie czy udalo sie faktycznie otworzyc
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    //zmienna pomocnicza do wczytywania tekstu typu "PADDLE", "BALL", "BLOCKS_COUNT"
    std::string label;

    //wczytanie paletki
    file >> label >> paddlePosition.x >> paddlePosition.y;

    //wczytanie pi³ki
    file >> label >> ballPosition.x >> ballPosition.y
        >> ballVelocity.x >> ballVelocity.y;

    //wczytanie liczby bloków
    size_t count;
    file >> label >> count;

    //wczytaj bloki 
    blocks.clear();
    blocks.reserve(count);

    //czytamy tyle bloków, ile by³o zapisanych, ka¿dy blok : jego pozycjê x, y, hp.
    //tworzymy strukturê dla ka¿dego bloku i dodajemy j¹ do listy snapshotu (to ze struktura).
    for (size_t i = 0; i < count; i++)
    {
        BlockData d;
        file >> d.x >> d.y >> d.hp;
        blocks.push_back(d);
    }

    if (file >> label >> score)   // label powinno byæ "SCORE"
    {
        // OK, score wczytany
    }

    //zamykamy plik
    file.close();
    return true;
}

void gameState::apply(Paddle& paddle, Ball& ball, std::vector<Brick>& blocksOut, float blockW, float blockH)
{
    //Paletka
    paddle.setPosition(paddlePosition);

    //Pilka
    ball.setPosition(ballPosition);
    ball.setVelocity(ballVelocity);

    //Bloki
    blocksOut.clear();
    for (const auto& b : blocks)
    {
        blocksOut.emplace_back(
            sf::Vector2f(b.x, b.y),
            sf::Vector2f(blockW, blockH),
            b.hp
        );
    }
}
