#pragma once

#include <SFML/Graphics.hpp>

struct Tile
{

	enum Type : char
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

	Tile();

	Tile(Type _type);

	static float MoveSpeed(Type type);

	static sf::Image* Image(Type type);
};
