#pragma once

#include <Vector2.hpp>
#include <Tile.hpp>
#include <Noise.hpp>
#include <GameObject.hpp>

class MapGenerator
{
	int m_seed;
	my::Noise_Output* m_dataHeight;
	my::Noise_Output* m_dataTemp;
	my::Noise_Output* m_dataDeposit;
	Vector2I m_size;
	std::vector<Tile*> m_ground;
	std::list<GameObject> m_objects;
	GameObject* m_groundObject;

public:
	const int m_texturesSize = 16;
	MapGenerator() = default;
	MapGenerator(Vector2I size);
	MapGenerator(const MapGenerator& other) = delete;
	MapGenerator& operator=(const MapGenerator& other) = delete;
	~MapGenerator();

	my::Noise_Output& getDataHeight() { return *m_dataHeight; }
	my::Noise_Output& getDataTemp() { return *m_dataTemp; }
	my::Noise_Output& getDataDeposit() { return *m_dataDeposit; }

	Tile* const getTile(int x, int y);
	Tile* const getTile(sf::Vector2i pos);
	const Vector2I& getSize();
	sf::Vector2f GridCoordsToCenterCoords(int x, int y);
	sf::Vector2f GridCoordsToCoords(int x, int y);
	sf::Vector2f CoordsToGridCoords(sf::Vector2f pos);

	sf::Vector2f getPlayerCoordsSpawn();
};
