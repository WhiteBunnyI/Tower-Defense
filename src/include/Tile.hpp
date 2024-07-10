#pragma once

#include <SFML/Graphics.hpp>

struct Tile
{
	enum class Type : char
	{
		water,
		soil,
		grass,
		sand,
		road,
		rock,
		rocky_surface,
		snow,
	};

	Type type;
	float speed;

	Tile(Type type);

	static float MoveSpeed(Type type);

	static sf::Image* Image(Type type);
	friend class MapGenerator;
private:
	void resetSpeed();
};
