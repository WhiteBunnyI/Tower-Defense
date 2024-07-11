#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:

	void SetPosition(sf::Vector2f pos);
	void Move(sf::Vector2f vector);
	void Move(float offsetX, float offsetY);
};
