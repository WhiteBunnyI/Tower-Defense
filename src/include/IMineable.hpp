#pragma once

#include <Resources.hpp>

class IMineable
{
protected:
	int m_health;
	Resources::resource type;
public:
	void Mine();
};