#include <GameObject.hpp>

GameObject::GameObject() : IUpdateable(), IStartable(), IRenderable() { }

GameObject::GameObject(const sf::Vector2f position, sf::Texture* texture) : IUpdateable(), IStartable(), IRenderable(texture)
{
	render->setPosition(position);
}

GameObject::GameObject(const GameObject& other) : GameObject()
{
	render->setTexture(*other.render->getTexture());
	render->setPosition(other.render->getPosition());
	render->setColor(other.render->getColor());
	render->setOrigin(other.render->getOrigin());
}

GameObject& GameObject::operator=(const GameObject& other)
{
	if(this != nullptr && render != nullptr)
		delete render;
	render = new sf::Sprite(*other.render->getTexture());
	render->setPosition(other.render->getPosition());
	render->setColor(other.render->getColor());
	render->setOrigin(other.render->getOrigin());
	return *this;
}


