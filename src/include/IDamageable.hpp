#pragma once

class IDamageable
{
protected:
	int m_health;
public:
	virtual void Damage(int damage) = 0;
};