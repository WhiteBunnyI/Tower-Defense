#pragma once

#include <IUpdateable.hpp>

//#define DEBUG_PATHFINDING

class Mouse : IUpdateable
{
	//sf::RenderWindow* window;
	//Input* input;
	//
	//Vector2I a;
	//Vector2I b;
	//
	//my::pathFinding::PathFinding finder;
	//std::future<my::pathFinding::Node*> result;
	//bool isCalculatePath;

	Input* input;

public:

	Mouse();

	void Update() override;

};

#include <Engine.hpp>
