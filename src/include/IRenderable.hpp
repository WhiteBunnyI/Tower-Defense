#pragma once

#include <SFML/Graphics.hpp>

struct IRenderable
{
	sf::Sprite* render;
	IRenderable(sf::Texture* t);

	virtual ~IRenderable();

	void Clear();
};