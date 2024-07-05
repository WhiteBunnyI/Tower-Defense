#include <GameObject.hpp>


void GameObject::Initialize()
{
	Engine::instance->m_gameObjects.push_back(this);
}
	
GameObject::GameObject()
{
	render = sf::Sprite();
	Initialize();
}

GameObject::GameObject(Vector2 position, sf::Texture* texture) : GameObject()
{
	if (texture != nullptr)
		render.setTexture(*texture, true);
	render.setPosition(position.x, position.y);
	Initialize();
}

GameObject::GameObject(const GameObject& other) : render{ other.render } {}

GameObject& GameObject::operator=(const GameObject& other)
{
	render = other.render;
	return *this;
}

GameObject::~GameObject()
{
	delete render.getTexture();
}

void GameObject::SetScale(Vector2& scale)
{
	SetScale(scale.x, scale.y);
}
void GameObject::SetScale(float x, float y)
{
	render.setScale(x, y);
}

void GameObject::SetPosition(Vector2& pos)
{
	SetPosition(pos.x, pos.y);
}
void GameObject::SetPosition(float x, float y)
{
	render.setPosition(x, y);
}


