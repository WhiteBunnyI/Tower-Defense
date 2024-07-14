#pragma once

#include <GameObject.hpp>
#include <IMineable.hpp>
#include <Collision.hpp>

class Deposit : public GameObject, public IMineable
{
	Collision::CircleCollider collider;

public:
	Deposit(const sf::Vector2f position, sf::Texture* texture, int health, int resourceCount, Resources::resource typeResource);

	int Mine(int damage) override;
};