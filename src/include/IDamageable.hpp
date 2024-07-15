#pragma once

class IHittable
{
protected:
	int m_health;
public:
	IHittable(int health) : m_health{ health } {}
	virtual ~IHittable() = default;
	//true - is dead
	virtual bool Hit(int damage) = 0;
};