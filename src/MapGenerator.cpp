#include <MapGenerator.hpp>
#include <Engine.hpp>
#include <Resources.hpp>
#include <Deposit.hpp>
#include <Building.hpp>

MapGenerator::MapGenerator(Vector2I size, int textureSize) :
	m_seed{ std::rand() },
	m_size{ size },
	m_dataHeight{ my::Perlin_Noise::GetNoise(m_seed, Vector2I(20,20), size) },
	m_dataTemp{ my::Perlin_Noise::GetNoise(m_seed, Vector2I(2, 2), size) },
	m_dataDeposit{ my::Perlin_Noise::GetNoise(m_seed, Vector2I(50,50), size) },
	m_texturesSize{ textureSize }
{
	m_ground.resize(size.x * size.y);
	m_objects.resize(size.x * size.y);
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

	sf::Image* treeIm = Resources::Image(Resources::resource::wood);
	sf::Image* ironIm = Resources::Image(Resources::resource::iron);
	sf::Image* goldIm = Resources::Image(Resources::resource::gold);
	sf::Image* rockIm = Resources::Image(Resources::resource::rock);

	sf::Texture* tree = new sf::Texture();
	tree->loadFromImage(*treeIm);
	sf::Texture* iron = new sf::Texture();
	iron->loadFromImage(*ironIm);
	sf::Texture* gold = new sf::Texture();
	gold->loadFromImage(*goldIm);
	sf::Texture* rockObj = new sf::Texture();
	rockObj->loadFromImage(*rockIm, sf::IntRect(0, 0, m_texturesSize, m_texturesSize));

	//sf::Texture* oil = Resources::Image(Resources::resource::oil);

	//Диапазон данных: 0-1, тип float
	//0 - низкая температура, 1 - высокая температура
	//[0   -  0.4]:	Снежный биом	(тип ресурсов: железо и золото)
	//(0.4 -  0.6]:	Лес				(тип ресурсов: древесина)
	//(0.6 -  1]:		Пустыня			(тип ресурсов: нефть?)
	for (int y = 0; y < m_size.y; ++y)
	{
		for (int x = 0; x < m_size.x; ++x)
		{
			auto b = (*m_dataTemp)[x][y];
			auto h = (*m_dataHeight)[x][y];

			//Пустыня
			if (b > 0.6f)
			{
				if (h >= 0.72f)
				{
					m_ground[x + y * m_size.x] = new Tile(Tile::Type::rock);
					map.copy(*rock, x * m_texturesSize, y * m_texturesSize);
					continue;
				}
				m_ground[x + y * m_size.x] = new Tile(Tile::Type::sand);
				map.copy(*sand, x * m_texturesSize, y * m_texturesSize);
				continue;
			}
			
			if (h >= 0.65f)
			{
				m_ground[x + y * m_size.x] = new Tile(Tile::Type::rock);
				map.copy(*rock, x * m_texturesSize, y * m_texturesSize);
				continue;
			}

			//Снежный биом
			if (b <= 0.4f)
			{
				m_ground[x + y * m_size.x] = new Tile(Tile::Type::snow);
				map.copy(*snow, x * m_texturesSize, y * m_texturesSize);
				continue;
			}

			//Лесной биом
			if (b <= 0.6f)
			{
				if (h >= 0.6f)
				{
					m_ground[x + y * m_size.x] = new Tile(Tile::Type::rocky_surface);
					map.copy(*rocky_surface, x * m_texturesSize, y * m_texturesSize);
					continue;
				}
				if (b >= 0.45f && b <= 0.55f)
				{
					if(b >= 0.455f && b <= 0.545f && h <= 0.35f)
					{
						m_ground[x + y * m_size.x] = new Tile(Tile::Type::water);
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
						m_ground[x + y * m_size.x] = new Tile(Tile::Type::soil);
						map.copy(*soil, x * m_texturesSize, y * m_texturesSize);
						continue;
					}
				}
				m_ground[x + y * m_size.x] = new Tile(Tile::Type::grass);
				map.copy(*grass, x * m_texturesSize, y * m_texturesSize);
				continue;
			}
			
		}
	}
	
	sf::Texture* texture = new sf::Texture();
	texture->loadFromImage(map);
	m_groundObject = new GameObject(sf::Vector2f(0, 0), texture);

	Deposit* dep;
	for (int y = 0; y < m_size.y; ++y)
	{
		for (int x = 0; x < m_size.x; ++x)
		{
			(m_ground[x + y * m_size.x])->resetSpeed();
			auto b = (*m_dataTemp)[x][y];
			auto d = (*m_dataDeposit)[x][y];
			auto h = (*m_dataHeight)[x][y];
			auto pos = GridCoordsToCenterCoords(x, y);

			if (d >= 0.75f)
			{
				if (b > 0.6f)
				{
					if (h >= 0.72f)
						continue;
					dep = new Deposit(pos, rockObj, 300, 30, Resources::resource::rock);
					dep->render->setOrigin(8, 8);
					m_objects[x + y * m_size.x] = dep;
					(m_ground[x + y * m_size.x])->speed *= Resources::MoveModification(Resources::resource::rock);
					continue;
				}
				if (b <= 0.4f)
				{
					if (h >= 0.65f)
						continue;

					if (d >= 0.8f)
					{
						dep = new Deposit(pos, gold, 300, 30, Resources::resource::gold);
						dep->render->setOrigin(8, 20);
						m_objects[x + y * m_size.x] = dep;
						(m_ground[x + y * m_size.x])->speed *= Resources::MoveModification(Resources::resource::gold);
						continue;
					}
					dep = new Deposit(pos, iron, 300, 30, Resources::resource::iron);
					dep->render->setOrigin(8, 20);
					m_objects[x + y * m_size.x] = dep;
					(m_ground[x + y * m_size.x])->speed *= Resources::MoveModification(Resources::resource::iron);
					continue;
				}
			}
			if (d >= 0.625f)
			{
				if (b <= 0.6f && b > 0.4f)
				{
					if (h < 0.6f && h > 0.41f)
					{
						dep = new Deposit(pos, tree, 15, 5, Resources::resource::wood);
						dep->render->setOrigin(8, 20);
						m_objects[x + y * m_size.x] = dep;
						(m_ground[x + y * m_size.x])->speed *= Resources::MoveModification(Resources::resource::wood);
					}
				}
					
			}
		}
	}

	delete water;
	delete soil;
	delete grass;
	delete sand;
	delete road;
	delete rock;
	delete rocky_surface;
	delete snow;
	delete treeIm;
	delete goldIm;
	delete ironIm;
	delete rockIm;
}

MapGenerator::~MapGenerator()
{
	if (m_dataHeight != nullptr)
		delete m_dataHeight;
	if (m_dataTemp != nullptr)
		delete m_dataTemp;
	if (m_groundObject != nullptr)
		delete m_groundObject;
}

Tile* const MapGenerator::getTile(int x, int y)
{
	if (x < 0 || y < 0 || x >= m_size.x || y >= m_size.y)
		return nullptr;
	return m_ground[x + y * m_size.x];
}

Tile* const MapGenerator::getTile(sf::Vector2i pos)
{
	return getTile(pos.x, pos.y);
}

GameObject*& MapGenerator::getObj(int x, int y)
{
	GameObject* temp;
	if (m_objects.empty())
		return temp;
	return m_objects[x + y * m_size.x];
}

GameObject*& MapGenerator::getObj(sf::Vector2i pos)
{
	return getObj(pos.x, pos.y);
}

bool MapGenerator::IsBuilding(int x, int y)
{
	GameObject* obj = getObj(x, y);
	if (obj == nullptr)
		return false;
	return dynamic_cast<Building::Wall*>(obj) || dynamic_cast<Building::WorkStation*>(obj);
}

const Vector2I& MapGenerator::getSize()
{
	return m_size;
}

sf::Vector2f MapGenerator::GridCoordsToCenterCoords(int x, int y)
{
	return sf::Vector2f(x * m_texturesSize + m_texturesSize / 2, y * m_texturesSize + m_texturesSize / 2);
}

sf::Vector2f MapGenerator::GridCoordsToCoords(int x, int y)
{
	return sf::Vector2f(x * m_texturesSize, y * m_texturesSize);
}

sf::Vector2f MapGenerator::CoordsToGridCoords(sf::Vector2f pos)
{
	return sf::Vector2f(pos.x / m_texturesSize, pos.y / m_texturesSize);
}

sf::Vector2f MapGenerator::getPlayerCoordsSpawn()
{
	int _x = m_size.x / 2;
	int _y = m_size.y / 2;
	if (m_ground[_x + _y * m_size.x]->type == Tile::Type::grass)
	{
		return GridCoordsToCenterCoords(m_size.x / 2, m_size.y / 2);
	}

	for (int r = 1; r < std::min(m_size.x, m_size.y) / 2; ++r)
	{
		for (int y = -r; y <= r; ++y)
		{
			for (int x = -r; x <= r; ++x)
			{
				if (m_ground[(x + _x) + (y + _y) * m_size.x]->type == Tile::Type::grass)
				{
					return GridCoordsToCenterCoords(x + _x, y + _y);
				}
			}
		}
	}

	return sf::Vector2f(0, 0);
}
