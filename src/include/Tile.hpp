#pragma once

#include <SFML/Graphics.hpp>

struct Tile
{

	enum class Type
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

	static float MoveSpeed(Type type);

	static sf::Image* Image(Type type);
};
