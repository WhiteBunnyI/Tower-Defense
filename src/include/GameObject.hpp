#pragma once

#include <Vector2.hpp>
#include <SFML/Graphics.hpp>

class GameObject
{
	sf::Sprite render;

	void Initialize();
	
	friend class Engine;

public:

	
	GameObject();

	GameObject(Vector2 position, sf::Texture* texture);

	GameObject(const GameObject& other);

	GameObject& operator=(const GameObject& other);

	virtual void Start() { };

	virtual void Update() { };

	virtual ~GameObject();

	void SetScale(Vector2& scale);
	void SetScale(float x, float y);

	void SetPosition(Vector2& pos);
	void SetPosition(float x, float y);

};

#include <Engine.hpp>
