#include <Engine.hpp>
#include <Camera.hpp>
#include <Coroutine.hpp>
#include <Mouse.hpp>
#include <Singleton.hpp>
#include <PathFinding.hpp>
#include <Player.hpp>
#include <Enemy.hpp>

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
	Engine engine(800, 600, sf::Vector2i(20, 20), sf::Vector2i(200 * 16, 200 * 16));

	Singleton singleton;
	MapGenerator map(Vector2I(200, 200), 16);
	singleton.map = &map;

	sf::Image height(NoiseToImage(map.getDataHeight()));
	sf::Image temp(NoiseToImage(map.getDataTemp()));
	sf::Image deposits(NoiseToImage(map.getDataDeposit()));
	height.saveToFile("./HeightMap.png");
	temp.saveToFile("./TempMap.png");
	deposits.saveToFile("./DepositMap.png");

	Player player(120, 2);
	singleton.player = &player;
	sf::Texture* enemyTexture = new sf::Texture();
	enemyTexture->loadFromFile("./resources/MiniWorldSprites/Characters/Monsters/Slimes");
	Enemy enemy(player.render->getPosition() - sf::Vector2f(32, 0), enemyTexture);

	engine.CrankUp();

	return 0;
}