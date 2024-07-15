#pragma once

#include <SFML/Graphics.hpp>
#include <GameObject.hpp>
#include <IDamageable.hpp>
#include <Resources.hpp>
#include <unordered_map>
#include <Collision.hpp>
#include <Keep.hpp>

class Building
{
public:
	class Wall;

	class Archer : public GameObject, public IHittable
	{
		Collision::CircleCollider collider;
		Collision::CircleCollider attackTrigger;
		friend class Wall;
		friend class BuildSystem;
	public:
		Archer(const sf::Vector2f position, sf::Texture* texture, int health);
		~Archer() override = default;

		bool Hit(int damage) override;
	};

	class Wall : public GameObject, public IHittable
	{
		Archer* archer;
		Collision::CircleCollider collider;
		friend class BuildSystem;
	public:
		Wall(const sf::Vector2f position, sf::Texture* texture, int health);
		~Wall() override;

		bool PlaceArcher(sf::Texture& texture);
		bool Hit(int damage) override;
	};

	class WorkStation : public GameObject, public IHittable
	{
		Resources::resource m_typeOfResource;
		Collision::CircleCollider gatherCollider;
		Collision::CircleCollider collider;
		int m_resourcesPer15sec;
		float m_timer;
		bool isWorking;
		friend class BuildSystem;
	public:
		WorkStation(const sf::Vector2f position, sf::Texture* texture, int health);
		WorkStation(const sf::Vector2f position, sf::Texture* texture, int health, Resources::resource typeOfResource, int resourcesPer15sec);
		~WorkStation() override = default;

		void Update() override;

		bool Hit(int damage) override;
	};
};

class BuildSystem
{
	sf::Image resources;
	sf::Image wall_1;
	sf::Image wall_2;
	sf::Image wall_3;
	sf::Image keep;
	sf::Image barracks;
	sf::Image archers;

	GameObject* getGameObjectInGrid(sf::Vector2f pos);
	GameObject* getGameObjectInGrid(int x, int y);

public:

	enum class Buildings
	{
		wall_1,
		wall_2,
		wall_3,
		cave,
		lumber,
		archerBarrack,
		archer,
		//swordsmanBarrack
		keep_1,
		keep_2,
		keep_3,

		nothing,
	};

	std::unordered_map<Buildings, Resources> resourceRequire =
	{
		{Buildings::wall_1, Resources(3)},
		{Buildings::wall_2, Resources(5,0,0,3)},
		{Buildings::wall_3, Resources(5,0,0,6)},
		{Buildings::keep_1, Resources(20)},
		{Buildings::keep_2, Resources(50, 10, 15, 30)},
		{Buildings::keep_3, Resources(100, 50, 100, 100)},
		{Buildings::cave, Resources(15)},
		{Buildings::lumber, Resources(10)},
		{Buildings::archerBarrack, Resources(30, 15, 80, 15)},
		{Buildings::archer, Resources(0, 0, 0, 0, 1)}
		//{Buildings::swordsmanBarrack, Resources(30, 20, 50, 15)}
	};

	int buildLevel;
	GameObject* building;
	GameObject* keepObj;
	sf::Vector2f prevPos;

	sf::Texture wall_1_t;
	sf::Texture wall_1_v;
	sf::Texture wall_1_h;

	sf::Texture wall_2_t;
	sf::Texture wall_2_v;
	sf::Texture wall_2_h;

	sf::Texture wall_3_t;
	sf::Texture wall_3_v;
	sf::Texture wall_3_h;

	sf::Texture keep_1;
	sf::Texture keep_2;
	sf::Texture keep_3;

	sf::Texture cave;
	sf::Texture lumber;

	sf::Texture archerBarrack;
	sf::Texture archer;
	//sf::Texture swordsmanBarrack;

	BuildSystem();

	bool CheckBuild(sf::Vector2f pos, Buildings type, GameObject*& building);

	void PlaceCurrentBuilding(Buildings type);

	void Build(sf::Vector2f pos, Buildings type, bool isBuild);

	void Destroy(sf::Vector2f pos);

	void Upgrade(sf::Vector2f pos);

};

