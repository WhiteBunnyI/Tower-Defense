#pragma once

#include <GameObject.hpp>
#include <Collision.hpp>
#include <IDamageable.hpp>

class Keep : public GameObject, public IHittable
{
	sf::RectangleShape* blackScreen;
	sf::Text* text;
	friend class Player;
	bool isDestroyed;
public:
	Collision::CircleCollider collider;
	Keep() = default;
	Keep(const sf::Vector2f position, sf::Texture* texture, int health);

	bool Hit(int damage) override;
};