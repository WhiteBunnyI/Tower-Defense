#include <GameObject.hpp>
#include <Engine.hpp>


void GameObject::Initialize()
{
	Engine::instance->m_gameObjects.push_back(*this);
}
	
GameObject::GameObject()
{
	Initialize();
}

GameObject::GameObject(const GameObject& other)
{
	*this = other;
}

GameObject& GameObject::operator=(const GameObject& other)
{
	position = other.position;
	return *this;
}



GameObject::GameObject(Vector2 position) : GameObject()
{
	this->position = position;
}
