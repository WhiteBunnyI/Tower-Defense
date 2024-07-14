#pragma once

#include <IDamageable.hpp>
#include <GameObject.hpp>
#include <PathFinding.hpp>
#include <ThreadPool.hpp>

class Enemy : GameObject, IDamageable
{
public:
	Enemy(const sf::Vector2f position, sf::Texture* texture);
};