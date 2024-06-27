#include <Tile.hpp>

Tile::Tile() : type{ Tile::water } { }

float Tile::MoveSpeed(Type type)
{
	switch (type)
	{
	case Tile::water:
		return 0;
	case Tile::soil:
		return 0.7f;
	case Tile::grass:
		return 0.6f;
	case Tile::sand:
		return 0.5f;
	case Tile::road:
		return 1;
	}
	return 0;
}

sf::Texture Tile::Texture(Type type)
{
	switch (type)
	{
	case Tile::water:
		break;
	case Tile::soil:
		break;
	case Tile::grass:
		break;
	case Tile::sand:
		break;
	case Tile::road:
		break;
	default:
		break;
	}
	return sf::Texture();
}

