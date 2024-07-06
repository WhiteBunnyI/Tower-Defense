#include <GameObject.hpp>
	
GameObject::GameObject() : IUpdateable(), IStartable(), IRenderable(nullptr) { }

GameObject::GameObject(Vector2 position, sf::Texture* texture) : IUpdateable(), IStartable(), IRenderable(texture)
{
	render->setPosition(position.x, position.y);
}

void GameObject::SetScale(Vector2& scale)
{
	SetScale(scale.x, scale.y);
}
void GameObject::SetScale(float x, float y)
{
	render->setScale(x, y);
}

void GameObject::SetPosition(Vector2& pos)
{
	SetPosition(pos.x, pos.y);
}
void GameObject::SetPosition(float x, float y)
{
	render->setPosition(x, y);
}


