#pragma once

#include <IDamageable.hpp>
#include <GameObject.hpp>
#include <PathFinding.hpp>
#include <ThreadPool.hpp>

class Enemy : GameObject, IDamageable
{
	my::pathFinding::PathFinding finder;
public:
	Enemy(const sf::Vector2f position, sf::Texture* texture);
	void Update() override;
	void Start() override;

};