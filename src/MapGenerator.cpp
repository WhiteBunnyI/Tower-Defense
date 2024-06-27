#include <MapGenerator.hpp>

MapGenerator::MapGenerator() : m_mapSizeX{ 0 }, m_mapSizeY{ 0 }, seed{ 0 }, m_data{}, m_map{ nullptr } { }

MapGenerator::MapGenerator(int sizeX, int sizeY)
{
	m_mapSizeX = sizeX;
	m_mapSizeY = sizeY;
	m_map = new Tile[sizeX*sizeY];
	std::srand(time(0));
	seed = std::rand();
	sf::Image im = Perlin_Noise(seed, Vector2(20,20), Vector2(sizeX, sizeY));
	im.saveToFile("noise.png");
	m_data = new sf::Texture();
	m_data->create(sizeX, sizeY);
	m_data->loadFromImage(im);
	//m_data.update(im);
	sf::Sprite* p_spr = new sf::Sprite();
	//spr->setScale(8, 8);
	p_spr->setTexture(*m_data);
	p_spr->setPosition(200, 200);
	Engine::instance->m_drawable.push_back(p_spr);
}

MapGenerator::~MapGenerator()
{
	if(m_map != nullptr)
		delete [] m_map;
	m_map = nullptr;
}

MapGenerator& MapGenerator::operator=(const MapGenerator& other)
{
	m_mapSizeX = other.m_mapSizeX;
	m_mapSizeY = other.m_mapSizeY;
	seed = other.seed;
	m_data = other.m_data;
	m_map = new Tile[m_mapSizeX * m_mapSizeY];
	for (int i = 0; i < m_mapSizeX * m_mapSizeY; i++)
	{
		m_map[i] = other.m_map[i];
	}
	return *this;
}

sf::Image MapGenerator::Perlin_Noise(int seed, Vector2 scale, Vector2 texSize)
{
	sf::Image im;
	im.create(texSize.x, texSize.y, sf::Color::Red);
	std::srand(seed);

	Vector2* r_vectors = new Vector2[(scale.x + 1) * (scale.y + 1)];

	for (int y = 0; y <= scale.y; ++y)
	{
		for (int x = 0; x <= scale.x; ++x)
		{
			int current = x + y * scale.x;
			float r_x = (std::rand() % 10000 - 5000) / 10000.f;
			float r_y = (std::rand() % 10000 - 5000) / 10000.f;
			
			Vector2 vec(r_x, r_y);
			vec.Normalize();

			r_vectors[current] = vec;
		}
	}

	float dx = std::floor(texSize.x / scale.x);
	float dy = std::floor(texSize.y / scale.y);

	//auto interpolation{ [](float x) {return ; } };
	auto interpolation{ [](float x) {return x * x * x * (10 + x * (6 * x - 15)); } };
	auto mix{ [](float x, float y, float a) {return (1 - a) * x + a * y; } };

	for (int y_s = 0; y_s < scale.y; ++y_s)
	{
		for (int x_s = 0; x_s < scale.x; ++x_s)
		{
			for (int y = 0; y < dy; ++y)
			{
				for (int x = 0; x < dx; ++x)
				{
					sf::Uint8 c = 255;

					Vector2 v_lt(x / dx, y / dy);
					Vector2 v_rt(x / dx - 1.f, y / dy);
					Vector2 v_lb(x / dx, y / dy - 1.f);
					Vector2 v_rb(x / dx - 1.f, y / dy - 1.f);

					int indexLeftTop = x_s + y_s * scale.x;

					float dot1 = Vector2::Dot(r_vectors[indexLeftTop], v_lt);
					float dot2 = Vector2::Dot(r_vectors[indexLeftTop + 1], v_rt);
					float dot3 = Vector2::Dot(r_vectors[indexLeftTop + (int)scale.x], v_lb);
					float dot4 = Vector2::Dot(r_vectors[indexLeftTop + (int)scale.x + 1], v_rb);

					float int_x = interpolation(x / dx);
					float int_y = interpolation(y / dy);
					float st = mix(dot3, dot4, int_x);
					float uv = mix(dot1, dot2, int_x);
					float noise = mix(uv, st, int_y) * 0.5f + 0.5f;

					float n = (dot1 + dot2 + dot3 + dot4) / 4.f;

					c *= noise;

					sf::Color color(c, c, c);
					im.setPixel(x + x_s * dx, y + y_s * dy, color);
				}
			}
		}
	}

	delete[] r_vectors;

	return im;

	
}

