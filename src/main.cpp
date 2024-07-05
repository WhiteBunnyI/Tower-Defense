#include <Engine.hpp>
#include <Camera.hpp>
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
	std::srand(time(0));

	Engine engine(800, 600);
	MapGenerator map(Vector2I(200, 200));
	sf::Image height(NoiseToImage(map.getDataHeight()));
	sf::Image temp(NoiseToImage(map.getDataTemp()));
	height.saveToFile("./HeightMap.png");
	temp.saveToFile("./TempMap.png");
	engine.CrankUp();

	//Придумать, как это сделать :D
	Camera camera;
	void (Camera::*movePtr)(Vector2) = Camera::Move;
	auto o = sf::Event::KeyPressed;
	auto w = []() {camera.*movePtr(0, 1); }
	EventHolder onW(o, sf::Keyboard::W, []()());
	

	return 0;
}