#include <GameObject.hpp>

GameObject::GameObject() : IUpdateable(), IStartable(), IRenderable() { }

GameObject::GameObject(const sf::Vector2f position, sf::Texture* texture, bool addTextureToRemoveList) : IUpdateable(), IStartable(), IRenderable(texture, addTextureToRemoveList)
{
	render->setPosition(position);
}

GameObject::GameObject(const GameObject& other) : GameObject()
{
	render->setTexture(*other.render->getTexture());
	render->setPosition(other.render->getPosition());
}

GameObject& GameObject::operator=(const GameObject& other)
{
	delete render;
	render = new sf::Sprite(*other.render->getTexture());
	render->setPosition(other.render->getPosition());
	return *this;
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


