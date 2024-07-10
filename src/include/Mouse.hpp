#pragma once

#include <Coroutine.hpp>
#include <PathFinding.hpp>

#define DEBUG_PATHFINDING

class Mouse : IUpdateable
{
	Coroutine<Mouse*>* cor;
	sf::RenderWindow* window;
	
	Vector2I a;
	Vector2I b;

	my::pathFinding::PathFinding finder;

public:
	bool timer;

	Mouse();

	void Update() override;

};

#include <Engine.hpp>
