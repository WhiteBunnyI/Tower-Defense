#pragma once

#include <Vector2.hpp>


class GameObject
{
	void Initialize();

public:

	Vector2 position;
	
	GameObject();

	GameObject(Vector2 position);

	GameObject(const GameObject& other);

	GameObject& operator=(const GameObject& other);

	virtual void Start() { };

	virtual void Update() { };

};