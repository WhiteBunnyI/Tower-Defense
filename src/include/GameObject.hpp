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

	GameObject(const sf::Vector2f position, sf::Texture* texture, bool addTextureToRemoveList = false);

	GameObject(const GameObject& other);

	GameObject& operator=(const GameObject& other);

	void Update() override {}
	void Start() override {}

	~GameObject() override = default;

	void SetScale(Vector2& scale);
	void SetScale(float x, float y);

	void SetPosition(Vector2& pos);
	void SetPosition(float x, float y);

};
