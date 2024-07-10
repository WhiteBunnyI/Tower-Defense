#include <MapGenerator.hpp>
#include <Engine.hpp>

MapGenerator::MapGenerator(Vector2I size) :
	m_seed{ std::rand() },
	m_size{ size },
	m_dataHeight{ my::Perlin_Noise::GetNoise(m_seed, Vector2I(20,20), size) },
	m_dataTemp{ my::Perlin_Noise::GetNoise(m_seed, Vector2I(2, 2), size) },
	m_dataDeposit{ my::Perlin_Noise::GetNoise(m_seed, Vector2I(100,100), size) },
	m_objects{ new GameObject[size.x * size.y] }
{
	m_ground.resize(size.x * size.y);
	sf::Image map;
	map.create(size.x * m_texturesSize, size.y * m_texturesSize, sf::Color::Red);

	sf::Image* water = Tile::Image(Tile::Type::water);
	sf::Image* soil = Tile::Image(Tile::Type::soil);
	sf::Image* grass = Tile::Image(Tile::Type::grass);
	sf::Image* sand = Tile::Image(Tile::Type::sand);
	sf::Image* road = Tile::Image(Tile::Type::road);
	sf::Image* rock = Tile::Image(Tile::Type::rock);
	sf::Image* rocky_surface = Tile::Image(Tile::Type::rocky_surface);
	sf::Image* snow = Tile::Image(Tile::Type::snow);

	//Диапазон данных: 0-1, тип float
	//0 - низкая температура, 1 - высокая температура
	//0   -  0.3:	Снежный биом	(тип ресурсов: железо и золото)
	//0.3 -  0.6:	Лес				(тип ресурсов: древесина)
	//0.6 -  1:		Пустыня			(тип ресурсов: нефть?)
	for (int y = 0; y < m_size.y; ++y)
	{
		for (int x = 0; x < m_size.x; ++x)
		{
			auto b = (*m_dataTemp)[x][y];
			auto h = (*m_dataHeight)[x][y];

			if (b > 0.6f)
			{
				if (h >= 0.72f)
				{
					m_ground[x + y * m_size.x] = Tile::Type::rock;
					map.copy(*rock, x * m_texturesSize, y * m_texturesSize);
					continue;
				}
				m_ground[x + y * m_size.x] = Tile::Type::sand;
				map.copy(*sand, x * m_texturesSize, y * m_texturesSize);
				continue;
			}

			if (h >= 0.65f)
			{
				m_ground[x + y * m_size.x] = Tile::Type::rock;
				map.copy(*rock, x * m_texturesSize, y * m_texturesSize);
				continue;
			}

			if (b <= 0.4f)
			{
				m_ground[x + y * m_size.x] = Tile::Type::snow;
				map.copy(*snow, x * m_texturesSize, y * m_texturesSize);
				continue;
			}

			if (h >= 0.6f)
			{
				m_ground[x + y * m_size.x] = Tile::Type::rocky_surface;
				map.copy(*rocky_surface, x * m_texturesSize, y * m_texturesSize);
				continue;
			}

			if (b <= 0.6f)
			{
				if (b >= 0.45f && b <= 0.55f)
				{
					if(b >= 0.455f && b <= 0.545f && h <= 0.35f)
					{
						m_ground[x + y * m_size.x] = Tile::Type::water;
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
						m_ground[x + y * m_size.x] = Tile::Type::soil;
						map.copy(*soil, x * m_texturesSize, y * m_texturesSize);
						continue;
					}
				}
				m_ground[x + y * m_size.x] = Tile::Type::grass;
				map.copy(*grass, x * m_texturesSize, y * m_texturesSize);
				continue;
			}
			
		}
	}
	
	sf::Texture* texture = new sf::Texture();
	texture->loadFromImage(map);
	m_groundObject = new GameObject(Vector2(0, 0), texture);

	delete water, soil, grass, sand, road, rock, rocky_surface, snow;
}

MapGenerator::~MapGenerator()
{
	if (m_dataHeight != nullptr)
		delete m_dataHeight;
	if (m_dataTemp != nullptr)
		delete m_dataTemp;
	if (m_objects != nullptr)
		delete[] m_objects;
	if (m_groundObject != nullptr)
		delete m_groundObject;
}

const Tile::Type& MapGenerator::getTile(int x, int y)
{
	return m_ground[x + y * m_size.x];
}

const Vector2I& MapGenerator::getSize()
{
	return m_size;
}

sf::Vector2f MapGenerator::translateCoordsToGridCoords(int x, int y)
{
	return sf::Vector2f(x * m_texturesSize + m_texturesSize / 2, y * m_texturesSize + m_texturesSize / 2);
}

sf::Vector2f MapGenerator::getPlayerCoordsSpawn()
{
	int _x = m_size.x / 2;
	int _y = m_size.y / 2;
	if (m_ground[_x + _y * m_size.x] == Tile::Type::grass)
	{
		return translateCoordsToGridCoords(m_size.x / 2, m_size.y / 2);
	}

	for (int r = 1; r < std::min(m_size.x, m_size.y) / 2; ++r)
	{
		for (int y = -r; y <= r; ++y)
		{
			for (int x = -r; x <= r; ++x)
			{
				if (m_ground[(x + _x) + (y + _y) * m_size.x] == Tile::Type::grass)
				{
					return translateCoordsToGridCoords(x + _x, y + _y);
				}
			}
		}
	}

	return sf::Vector2f(0, 0);
}
