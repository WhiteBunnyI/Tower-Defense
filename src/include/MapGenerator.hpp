#pragma once

#include <Tile.hpp>
#include <Vector2.hpp>


class MapGenerator
{
	int m_mapSizeX;
	int m_mapSizeY;
	int seed;
	sf::Texture* m_data;
	Tile* m_map;

public:
	MapGenerator();
	MapGenerator(int sizeX, int sizeY);
	MapGenerator(const MapGenerator& other) = delete;
	MapGenerator& operator=(const MapGenerator& other);
	~MapGenerator();

	static sf::Image Perlin_Noise(int seed, Vector2 scale, Vector2 texSize);
};

#include <Engine.hpp>