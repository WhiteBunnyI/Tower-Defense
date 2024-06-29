#include <MapGenerator.hpp>

MapGenerator::MapGenerator(Vector2 size) : m_seed{std::rand()}, 
	m_dataHeight{ my::Perlin_Noise::GetNoise(m_seed, Vector2I(10,10), Vector2I(size.x, size.y)) },
	m_dataTemp{ my::Perlin_Noise::GetNoise(m_seed, Vector2I(4, 4), Vector2I(size.x, size.y)) }
{
	m_mapSizeX = size.x;
	m_mapSizeY = size.y;
	m_map = new Tile[m_mapSizeX * m_mapSizeY];
	my::Noise_Output temp(my::Perlin_Noise::GetNoise(m_seed, Vector2I(10, 10), Vector2I(size.x, size.y)));
}

MapGenerator::~MapGenerator()
{
	if(m_map != nullptr)
		delete [] m_map;
	m_map = nullptr;
}

