#include <Tile.hpp>

Tile::Tile() : type{ Tile::water } { }

Tile::Tile(Type _type) : type{ _type } { }

float Tile::MoveSpeed(Type type)
{
	switch (type)
	{
	case Tile::water:
	case Tile::rock:
		return 0;

	case Tile::soil:
	case Tile::rocky_surface:
		return 0.7f;

	case Tile::grass:
		return 0.6f;

	case Tile::sand:
	case Tile::snow:
		return 0.5f;

	case Tile::road:
		return 1;
	}
	return 0;
}

sf::Image* Tile::Image(Type type)
{
	sf::Image* result = new sf::Image();
	switch (type)
	{
	case Tile::water:
		result->loadFromFile("./resources/environment/water.png");
		break;
	case Tile::soil:
		result->loadFromFile("./resources/environment/soil.png");
		break;
	case Tile::grass:
		result->loadFromFile("./resources/environment/grass.png");
		break;
	case Tile::sand:
		result->loadFromFile("./resources/environment/sand.png");
		break;
	case Tile::road:
		result->loadFromFile("./resources/environment/road.png");
		break;
	case Tile::rock:
		result->loadFromFile("./resources/environment/rock.png");
		break;
	case Tile::rocky_surface:
		result->loadFromFile("./resources/environment/rocky_surface.png");
		break;
	case Tile::snow:
		result->loadFromFile("./resources/environment/snow.png");
		break;
	default:
		break;
	}
	return result;
}

