#pragma once

#include <Tile.hpp>
#include <Noise.hpp>
#include <Vector2.hpp>

class MapGenerator
{
	int m_seed;
	my::Noise_Output* m_dataHeight;
	my::Noise_Output* m_dataTemp;
	Vector2I m_size;
	Tile* m_map;
	sf::Sprite m_mapObject;

public:
	const int m_texturesSize = 16;
	MapGenerator() = default;
	MapGenerator(Vector2I size);
	MapGenerator(const MapGenerator& other) = delete;
	MapGenerator& operator=(const MapGenerator& other) = delete;
	~MapGenerator();

	my::Noise_Output& getDataHeight() { return *m_dataHeight; }

	my::Noise_Output& getDataTemp() { return *m_dataTemp; }

	const Tile& getTile(int x, int y);
	const Vector2I& getSize();
	sf::Vector2f& translateCoordsToGridCoords(int x, int y);
};

#include <Engine.hpp>