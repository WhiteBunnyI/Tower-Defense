#include <Engine.hpp>

sf::Image NoiseToImage()
{
	sf::Image result;
	Engine::instance->map;
	return result;
}

int main()
{
	std::srand(time(0));

	Engine engine;

	engine.CrankUp(800, 600);
	return 0;
}