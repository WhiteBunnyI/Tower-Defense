#pragma once

#include <GameObject.hpp>
#include <IDamageable.hpp>
#include <Vector2.hpp>
#include <IMovable.hpp>
#include <IPlaceable.hpp>
#include <Resources.hpp>

class Tower : public GameObject, public IHittable, public IMovable, public IPlaceable
{
	int m_hp;
	TypeOfTowers m_type;

public:

	Tower(Vector2 position) : GameObject(position, nullptr), IHittable(0)
	{
		m_type = TypeOfTowers::squad_one;
	}
	
	bool Hit(int damage) override
	{

	}

	void Move(Vector2 newPos) override
	{

	}

	void Place(Vector2 at) override
	{

	}
};


enum TypeOfTowers : char
{
	squad_one,
	squad_two,
	squad_three,

	dot_one,
	dot_two,
	dot_three,

	heavySquad_one,
	heavySquad_two,
	heavySquad_three,

	mobileSquad_one,
	moblieSquad_two,
	mobileSquad_three,

};

struct TowerSettings
{
	int hp;
	int damage;
	int tilesPerSec;
	int experience;
	int experienceForLevelUp;
	Resources needToBuild;
	TypeOfTowers currentType;
	TypeOfTowers nextType;
};

