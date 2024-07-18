#pragma once

#include <IHittable.hpp>
#include <GameObject.hpp>
#include <PathFinding.hpp>
#include <mutex>
#include <Collision.hpp>
#include <forward_list>

//#define DEBUG_PATHFINDING

class Enemy : public GameObject, public IHittable, public ILateUpdateable
{
	float moveTimer;
	float attackTimer;

	//1 = одна клетка в секунду при условии, что скорость данной клетки равна 1
	float speed;
	float attackCooldown;
	int damage;
	bool isDead;
	bool isCalculatingPath;

	my::pathFinding::PathFinding finder;

	sf::Vector2f playerPos;
	sf::Vector2f currentPos;
	sf::Vector2f startPos;
	sf::Vector2i currentPosTarget;
	std::forward_list<sf::Vector2i> path;

	std::mutex m;
	Collision::CircleCollider collider;
	Collision::CircleCollider attackTrigger;

	std::function<void()> calculateFunc;

#ifdef DEBUG_PATHFINDING

	std::list<sf::Drawable*> tempList;

#endif // DEBUG_PATHFINDING


public:
	Enemy(const sf::Vector2f position, sf::Texture* texture, int health, int damage, float moveSpeed, float attackCooldown);
	~Enemy() override = default;
	void Update() override;
	void Start() override;
	void LateUpdate() override;
	bool Hit(int damage) override;
	void Attack();
	void Attack(int x, int y);
};