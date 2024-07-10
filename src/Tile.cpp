#include <Tile.hpp>

Tile::Tile(Type type) : type{ type }, speed{ MoveSpeed(type) } {}

void Tile::resetSpeed()
{
	speed = MoveSpeed(type);
}


float Tile::MoveSpeed(Type type)
{
	switch (type)
	{
	case Tile::Type::water:
	case Tile::Type::rock:
		return 0;

	case Tile::Type::grass:
		return 0.7f;

	case Tile::Type::rocky_surface:
		return 0.85f;

	case Tile::Type::soil:
		return 0.55f;

	case Tile::Type::sand:
	case Tile::Type::snow:
		return 0.5f;

	case Tile::Type::road:
		return 1;
	}
	return 0;
}

sf::Image* Tile::Image(Type type)
{
	sf::Image* result = new sf::Image();
	switch (type)
	{
	case Tile::Type::water:
		result->loadFromFile("./resources/environment/water.png");
		break;
	case Tile::Type::soil:
		result->loadFromFile("./resources/environment/soil.png");
		break;
	case Tile::Type::grass:
		result->loadFromFile("./resources/environment/grass.png");
		break;
	case Tile::Type::sand:
		result->loadFromFile("./resources/environment/sand.png");
		break;
	case Tile::Type::road:
		result->loadFromFile("./resources/environment/road.png");
		break;
	case Tile::Type::rock:
		result->loadFromFile("./resources/environment/rock.png");
		break;
	case Tile::Type::rocky_surface:
		result->loadFromFile("./resources/environment/rocky_surface.png");
		break;
	case Tile::Type::snow:
		result->loadFromFile("./resources/environment/snow.png");
		break;
	default:
		break;
	}
	return result;
}

