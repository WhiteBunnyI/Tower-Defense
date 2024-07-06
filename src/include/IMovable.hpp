#pragma once
#include <Vector2.hpp>

class IMovable
{
public:
	virtual void Move(Vector2 newPos) = 0;
	virtual void Move(float x, float y) = 0;
};