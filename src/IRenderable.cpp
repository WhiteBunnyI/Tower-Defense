#include <Engine.hpp>
#include <SFML/Graphics.hpp>

IRenderable::IRenderable(sf::Texture* t) : render{nullptr}
{
	if (t != nullptr)
		render = new sf::Sprite(*t);
	else
		render = new sf::Sprite();
	Engine::instance->m_render.push_back(this);
}

IRenderable::~IRenderable()
{
	Clear();
}

void IRenderable::Clear()
{
	if (render != nullptr)
	{
		if (render->getTexture() != nullptr)
			delete render->getTexture();
		delete render;
	}
	Engine::instance->m_render.remove(this);
}
	
