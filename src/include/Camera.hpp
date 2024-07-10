#pragma once

#include <Engine.hpp>

class Camera
{
public:

	void SetPosition(sf::Vector2f pos)
	{
		Engine::instance->m_view->setCenter(pos);
		Engine::instance->UpdateView();
	}
	void Move(sf::Vector2f vector)
	{
		Engine::instance->m_view->move(vector);
		Engine::instance->UpdateView();
	}
	void Move(float offsetX, float offsetY)
	{
		Engine::instance->m_view->move(offsetX, offsetY);
		Engine::instance->UpdateView();
	}
};
