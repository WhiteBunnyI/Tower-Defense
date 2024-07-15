#pragma once

#include <map>
#include <Engine.hpp>

class Resources
{
public:

	enum class resource
	{
		wood,
		iron,
		gold,
		rock,
		archer,

		nothing,
	};

	std::map<resource, int> resources;

	Resources(int wood = 0, int iron = 0, int gold = 0, int rock = 0, int archer = 0)
	{
		resources[resource::wood] = wood;
		resources[resource::iron] = iron;
		resources[resource::gold] = gold;
		resources[resource::rock] = rock;
		resources[resource::archer] = archer;
	}

	bool operator<=(Resources& other)
	{
		if ((resources[resource::wood] > other.resources[resource::wood]) ||
			(resources[resource::iron] > other.resources[resource::iron]) ||
			(resources[resource::gold] > other.resources[resource::gold]) ||
			(resources[resource::rock] > other.resources[resource::rock]) ||
			(resources[resource::archer] > other.resources[resource::archer]))
			return false;
		return true;
	}

	Resources& operator-=(Resources& other)
	{
		resources[resource::wood] -= other.resources[resource::wood];
		resources[resource::iron] -= other.resources[resource::iron];
		resources[resource::gold] -= other.resources[resource::gold];
		resources[resource::rock] -= other.resources[resource::rock];
		resources[resource::archer] -= other.resources[resource::archer];
		return *this;
	}

	static sf::Image* Image(resource type)
	{
		sf::Image* result = new sf::Image();
		switch (type)
		{
		case Resources::resource::wood:
			result->loadFromFile("./resources/environment/tree.png");
			break;
		case Resources::resource::iron:
			result->loadFromFile("./resources/environment/deposit_iron.png");
			break;
		case Resources::resource::gold:
			result->loadFromFile("./resources/environment/deposit_gold.png");
			break;
		case Resources::resource::rock:
			result->loadFromFile("./resources/MiniWorldSprites/Nature/Rocks.png");
			break;
		default:
			break;
		}
		return result;
	}

	static float MoveModification(resource type)
	{
		switch (type)
		{
		case Resources::resource::wood:
			return 0.85f;
		case Resources::resource::iron:
		case Resources::resource::gold:
		case Resources::resource::rock:
			return 0.7f;
		}
		return 1.f;
	}
};
