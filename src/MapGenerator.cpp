#include <MapGenerator.hpp>

MapGenerator::MapGenerator(Vector2I size) : 
	m_seed{ std::rand() }, m_size{size},
	m_dataHeight{ my::Perlin_Noise::GetNoise(m_seed, Vector2I(20,20), Vector2I(size.x, size.y)) },
	m_dataTemp{ my::Perlin_Noise::GetNoise(m_seed, Vector2I(2, 2), Vector2I(size.x, size.y)) },
	m_map{ new Tile[size.x * size.y] }
{
	sf::Image map;
	map.create(size.x * m_texturesSize, size.y * m_texturesSize, sf::Color::Red);

	sf::Image* water = Tile::Image(Tile::water);
	sf::Image* soil = Tile::Image(Tile::soil);
	sf::Image* grass = Tile::Image(Tile::grass);
	sf::Image* sand = Tile::Image(Tile::sand);
	sf::Image* road = Tile::Image(Tile::road);
	sf::Image* rock = Tile::Image(Tile::rock);
	sf::Image* rocky_surface = Tile::Image(Tile::rocky_surface);
	sf::Image* snow = Tile::Image(Tile::snow);

	//Диапазон данных: 0-1, тип float
	//0 - низкая температура, 1 - высокая температура
	//0   -  0.3:	Снежный биом	(тип ресурсов: железо и золото)
	//0.3 -  0.6:	Лес				(тип ресурсов: древесина)
	//0.6 -  1:		Пустыня			(тип ресурсов: нефть)

	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			auto b = (*m_dataTemp)[x][y];
			auto h = (*m_dataHeight)[x][y];

			if (b > 0.6f)
			{
				if (h >= 0.72f)
				{
					m_map[x + y * m_size.x] = Tile(Tile::rock);
					map.copy(*rock, x * m_texturesSize, y * m_texturesSize);
					continue;
				}
				m_map[x + y * m_size.x] = Tile(Tile::sand);
				map.copy(*sand, x * m_texturesSize, y * m_texturesSize);
				continue;
			}

			if (h >= 0.65f)
			{
				m_map[x + y * m_size.x] = Tile(Tile::rock);
				map.copy(*rock, x * m_texturesSize, y * m_texturesSize);
				continue;
			}

			if (b <= 0.4f)
			{
				m_map[x + y * m_size.x] = Tile(Tile::snow);
				map.copy(*snow, x * m_texturesSize, y * m_texturesSize);
				continue;
			}

			if (h >= 0.6f)
			{
				m_map[x + y * m_size.x] = Tile(Tile::rocky_surface);
				map.copy(*rocky_surface, x * m_texturesSize, y * m_texturesSize);
				continue;
			}

			if (b <= 0.6f)
			{
				if (b >= 0.45f && b <= 0.55f)
				{
					if(b >= 0.455f && b <= 0.545f && h <= 0.35f)
					{
						m_map[x + y * m_size.x] = Tile(Tile::water);
						map.copy(*water, x * m_texturesSize, y * m_texturesSize);
						continue;
					}
					//if (h <= 0.39f)
					//{
					//	m_map[x + y * m_size.x] = Tile(Tile::sand);
					//	map.copy(*sand, x * m_texturesSize, y * m_texturesSize);
					//	continue;
					//}
					if (h <= 0.41f)
					{
						m_map[x + y * m_size.x] = Tile(Tile::soil);
						map.copy(*soil, x * m_texturesSize, y * m_texturesSize);
						continue;
					}
				}
				m_map[x + y * m_size.x] = Tile(Tile::grass);
				map.copy(*grass, x * m_texturesSize, y * m_texturesSize);
				continue;
			}
			
		}
	}
	//map.update(forest, 10, 10);
	sf::Texture* texture = new sf::Texture();
	texture->loadFromImage(map);
	GameObject* t = new GameObject(Vector2(0, 0), texture);
	float x = (float)Engine::instance->m_gameWidth / texture->getSize().x;
	float y = (float)Engine::instance->m_gameHeight / texture->getSize().y;
	//t->SetScale(x, y);

	delete water, soil, grass, sand, road, rock, rocky_surface, snow;
}

MapGenerator::~MapGenerator()
{
	if(m_map != nullptr)
		delete [] m_map;
	if (m_dataHeight != nullptr)
		delete m_dataHeight;
	if (m_dataTemp != nullptr)
		delete m_dataTemp;
}
