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

	//Придумать, как это сделать :D
	Camera camera(6);
	auto moveLambda{ [](sf::Event& event, EventHolder<Camera*>& holder)
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::W)
					holder.get<0>()->m_up = true;
				else if (event.key.code == sf::Keyboard::S)
					holder.get<0>()->m_down = true;
				else if (event.key.code == sf::Keyboard::A)
					holder.get<0>()->m_left = true;
				else if (event.key.code == sf::Keyboard::D)
					holder.get<0>()->m_right = true;
				break;

			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::W)
					holder.get<0>()->m_up = false;
				else if (event.key.code == sf::Keyboard::S)
					holder.get<0>()->m_down = false;
				else if (event.key.code == sf::Keyboard::A)
					holder.get<0>()->m_left = false;
				else if (event.key.code == sf::Keyboard::D)
					holder.get<0>()->m_right = false;
				break;
			}
		} 
	};
	EventHolder<Camera*> onW(moveLambda, &camera);

	
	engine.CrankUp();

	return 0;
}