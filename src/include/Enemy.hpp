#pragma once

#include <IDamageable.hpp>
#include <GameObject.hpp>
#include <PathFinding.hpp>

class Enemy : public GameObject, public IDamageable, public ILateUpdateable
{
	bool isDead;
	bool isCalculatingPath;
	my::pathFinding::PathFinding finder;
public:
	Enemy(const sf::Vector2f position, sf::Texture* texture, int health);
	void Update() override;
	void Start() override;
	void LateUpdate() override;
	void Damage(int damage) override;

};