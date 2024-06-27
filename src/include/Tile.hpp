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
	};

	Type type;

	Tile();

	static float MoveSpeed(Type type);

	static sf::Texture Texture(Type type);
};
