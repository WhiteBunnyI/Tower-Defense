#pragma once

#include <map>

class Resources
{
public:

	enum resource
	{
		wood,
		iron,
		gold
	};

	std::map<resource, int> resources{ {wood, 0}, {iron, 0}, {gold, 0} };
	
};