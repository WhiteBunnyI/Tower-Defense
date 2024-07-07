#pragma once

#include <Coroutine.hpp>

class Mouse : IUpdateable
{
	sf::RenderWindow* window;
public:
	bool timer;

	Mouse();

	void Update() override;

};

#include <Engine.hpp>
