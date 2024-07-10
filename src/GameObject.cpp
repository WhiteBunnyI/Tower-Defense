#include <GameObject.hpp>

GameObject::GameObject() : IUpdateable(), IStartable(), IRenderable() { }

GameObject::GameObject(sf::Vector2f position, sf::Texture* texture, bool addTextureToList) : IUpdateable(), IStartable(), IRenderable(texture, addTextureToList)
{
	render->setPosition(position);
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


