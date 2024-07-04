#include <MapGenerator.hpp>

MapGenerator::MapGenerator(Vector2I size) : 
	m_seed{ std::rand() }, m_size{size},
	m_dataHeight{ my::Perlin_Noise::GetNoise(m_seed, Vector2I(10,10), Vector2I(size.x, size.y)) },
	m_dataTemp{ my::Perlin_Noise::GetNoise(m_seed, Vector2I(2, 2), Vector2I(size.x, size.y)) },
	m_map{ new Tile[m_size.x * m_size.y] }
{
	sf::Image desert;
	sf::Image forest;
	sf::Image snow;
	sf::Image water;
	sf::Image map;
	map.create(size.x * m_texturesSize, size.y * m_texturesSize, sf::Color::Red);
	desert.loadFromFile("resources/environment/desert.png");
	forest.loadFromFile("resources/environment/forest.png");
	snow.loadFromFile("resources/environment/snow.png");
	water.loadFromFile("resources/environment/water.png");


	//Диапазон данных: 0-1, тип float
	//0 - низкая температура, 1 - высокая температура
	//0   -  0.3:	Снежный биом	(тип ресурсов: железо и золото)
	//0.3 -  0.6:	Лес				(тип ресурсов: древесина)
	//0.6 -  1:		Пустыня			(тип ресурсов: нефть)

	for (int y = 0; y < size.y; ++y)
	{
		for (int x = 0; x < size.x; ++x)
		{
			auto b = (*m_dataTemp)[x][y];
			auto h = (*m_dataHeight)[x][y];
			if (b <= 0.4f)
			{
				map.copy(snow, x * m_texturesSize, y * m_texturesSize);
			}
			else if (b <= 0.6f)
			{
				if (b >= 0.45f && b <= 0.55f && h <= 0.35f)
				{
					map.copy(water, x * m_texturesSize, y * m_texturesSize);
					continue;
				}
				map.copy(forest, x * m_texturesSize, y * m_texturesSize);
			}
			else
			{
				map.copy(desert, x * m_texturesSize, y * m_texturesSize);
			}
		}
	}
	//map.update(forest, 10, 10);
	sf::Texture* texture = new sf::Texture();
	texture->loadFromImage(map);
	auto t = new GameObject(Vector2(0, 0), texture);
	float x = (float)Engine::instance->m_gameWidth / texture->getSize().x;
	float y = (float)Engine::instance->m_gameHeight / texture->getSize().y;
	t->SetScale(x, y);
}

MapGenerator::~MapGenerator()
{
	if(m_map != nullptr)
		delete [] m_map;
}
