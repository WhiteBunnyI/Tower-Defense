#pragma once

#include <Resources.hpp>

class IMineable
{
protected:
	const int m_maxHealth;
	const int m_maxResource;
	int m_resourceCount;
	int m_health;
public:
	const Resources::resource type;
	IMineable(int resourceCount, int health, Resources::resource type) :
		m_resourceCount{ resourceCount },
		m_maxResource{ resourceCount },
		m_health{ health },
		m_maxHealth{ health },
		type{ type } {}
	virtual int Mine(int damage) = 0;
};