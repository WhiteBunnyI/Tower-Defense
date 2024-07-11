#include <Engine.hpp>
#include <Camera.hpp>
#include <Coroutine.hpp>
#include <Mouse.hpp>
#include <Singleton.hpp>
#include <PathFinding.hpp>
#include <Player.hpp>

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


int main()
{
	setlocale(LC_ALL, "rus");
	std::srand(time(0));
	Engine engine(800, 600);

	Singleton singleton;
	MapGenerator map(Vector2I(200, 200));
	singleton.map = &map;

	sf::Image height(NoiseToImage(map.getDataHeight()));
	sf::Image temp(NoiseToImage(map.getDataTemp()));
	sf::Image deposits(NoiseToImage(map.getDataDeposit()));
	height.saveToFile("./HeightMap.png");
	temp.saveToFile("./TempMap.png");
	deposits.saveToFile("./DepositMap.png");

	Player player(120, 2);

	engine.CrankUp();

	return 0;
}