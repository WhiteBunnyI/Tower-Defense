#pragma once

#include <IUpdateable.hpp>
#include <IStartable.hpp>
#include <IRenderable.hpp>
#include <Vector2.hpp>

class GameObject : public IUpdateable, public IStartable, public IRenderable
{
	friend class Engine;

public:
	
	GameObject();

	GameObject(const sf::Vector2f position, sf::Texture* texture);

	GameObject(const GameObject& other);

	GameObject& operator=(const GameObject& other);

	void Update() override {}
	void Start() override {}

	~GameObject() override = default;

};
