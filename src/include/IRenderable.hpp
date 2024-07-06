#pragma once

#include <SFML/Graphics.hpp>

struct IRenderable
{
	sf::Sprite* render;
	IRenderable(sf::Texture* t);

	~IRenderable();

	void Clear();
};