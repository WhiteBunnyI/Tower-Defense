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
		oil
	};

	std::map<resource, int> resources;

	Resources()
	{
		resources[resource::wood] = 0;
		resources[resource::iron] = 0;
		resources[resource::gold] = 0;
	}

	static sf::Texture* Image(resource type)
	{
		sf::Texture* result = new sf::Texture();
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
		case Resources::resource::oil:
			result->loadFromFile("./resources/environment/deposit_oil.png");
			break;
		default:
			break;
		}
		Engine::instance->m_textures.push_back(result);
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
		case Resources::resource::oil:
			return 0.7f;
		}
		return 1.f;
	}

};
