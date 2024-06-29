#include <MapGenerator.hpp>

MapGenerator::MapGenerator(Vector2 size) : m_seed{std::rand()}, 
	m_data1{ my::Perlin_Noise::GetNoise(m_seed, Vector2(10,10), Vector2(size.x, size.y)) },
	m_data2{ my::Perlin_Noise::GetNoise(m_seed, Vector2(4, 4), Vector2(size.x, size.y)) }
{
	m_mapSizeX = size.x;
	m_mapSizeY = size.y;
	m_map = new Tile[m_mapSizeX * m_mapSizeY];
}

MapGenerator::~MapGenerator()
{
	if(m_map != nullptr)
		delete [] m_map;
	m_map = nullptr;
}

