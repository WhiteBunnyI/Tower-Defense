#include <Engine.hpp>
#include <Camera.hpp>
#include <Coroutine.hpp>
#include <Mouse.hpp>
#include <Singleton.hpp>
#include <PathFinding.hpp>
#include <Player.hpp>
#include <Enemy.hpp>
#include <Waves.hpp>

#include <memory>

sf::Image NoiseToImage(my::Noise_Output& noise)
{
	sf::Image result;
	result.create(noise.getSize().x, noise.getSize().y);

	for (int x = 0; x < noise.getSize().x; ++x)
	{
		for (int y = 0; y < noise.getSize().y; ++y)
		{
			uint8_t p = noise[x][y] * 255;
			result.setPixel(x, y, sf::Color(p, p, p));
		}
	}

	return result;
}

struct Data
{
	float data1;
	float data2;

	Data(float d1, float d2) : data1{ d1 }, data2{ d2 } {}
};

int main()
{
	setlocale(LC_ALL, "rus");
	std::srand(time(0));

	int mapSize = 200;

	Engine engine(800, 600, sf::Vector2i(20, 20), sf::Vector2i(mapSize * 16, mapSize * 16));

	Singleton singleton;
	MapGenerator map(Vector2I(mapSize, mapSize), 16);
	singleton.map = &map;

	std::shared_ptr<Player> p1 = std::make_shared<Player>(3, 5);
	std::cout << p1.use_count() << std::endl;
	
	std::shared_ptr<Player> p2 = std::make_shared<Player>(3, 7);
	std::cout << p2.use_count() << std::endl;

	return 0;
	sf::Image height(NoiseToImage(map.getDataHeight()));
	sf::Image temp(NoiseToImage(map.getDataTemp()));
	sf::Image deposits(NoiseToImage(map.getDataDeposit()));
	height.saveToFile("./HeightMap.png");
	temp.saveToFile("./TempMap.png");
	deposits.saveToFile("./DepositMap.png");

	Player player(2, 2);
	singleton.player = &player;
	
	Waves waves;

	engine.CrankUp();

	return 0;
}