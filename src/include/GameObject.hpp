#pragma once

#include <IUpdateable.hpp>
#include <IStartable.hpp>
#include <IRenderable.hpp>
#include <Vector2.hpp>

class GameObject : public IUpdateable, public IStartable, public IRenderable
{
	friend class Engine;

protected:

	void Update() override {}
	void Start() override {}

public:
	
	GameObject();

	GameObject(const sf::Vector2f position, sf::Texture* texture);

	GameObject(const GameObject& other);

	GameObject& operator=(const GameObject& other);

	~GameObject() override = default;

};
