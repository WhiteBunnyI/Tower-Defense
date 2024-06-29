#pragma once

#include <Tile.hpp>
#include <Noise.hpp>
#include <Vector2.hpp>

class MapGenerator
{
	int m_seed;
	int m_mapSizeX;
	int m_mapSizeY;
	my::Noise_Output m_dataHeight;
	my::Noise_Output m_dataTemp;
	Tile* m_map;

public:
	MapGenerator() = default;
	MapGenerator(Vector2 size);
	MapGenerator(const MapGenerator& other) = delete;
	MapGenerator& operator=(const MapGenerator& other) = delete;
	~MapGenerator();

	my::Noise_Output& getData1() { return m_dataHeight; }

	my::Noise_Output& getData2() { return m_dataTemp; }

};

#include <Engine.hpp>