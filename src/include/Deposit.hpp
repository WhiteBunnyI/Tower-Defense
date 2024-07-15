#pragma once

#include <GameObject.hpp>
#include <IMineable.hpp>
#include <Collision.hpp>

class Deposit : public GameObject, public IMineable
{
	Collision::CircleCollider collider;
	bool isDestroyed;
public:
	Deposit(const sf::Vector2f position, sf::Texture* texture, int health, int resourceCount, Resources::resource typeResource);
	~Deposit() override;

	int Mine(int damage) override;

	bool IsDestroyed();
};