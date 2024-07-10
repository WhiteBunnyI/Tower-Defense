#include <Engine.hpp>
#include <SFML/Graphics.hpp>

IRenderable::IRenderable(sf::Texture* t, bool addTextureToList) : render{nullptr}
{
	if (t != nullptr)
		render = new sf::Sprite(*t);
	else
		render = new sf::Sprite();
	Engine::instance->m_render.push_back(this);
	if (addTextureToList)
		Engine::instance->m_textures.push_back(t);
}

IRenderable::~IRenderable()
{
	Clear();
}

void IRenderable::Clear()
{
	if (render != nullptr)
	{
		delete render;
	}
	Engine::instance->m_render.remove(this);
}
	
