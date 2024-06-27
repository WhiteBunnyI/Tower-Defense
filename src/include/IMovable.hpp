#pragma once
#include <Vector2.hpp>

class IMovable
{
public:
	virtual void Move(Vector2 newPos) = 0;
};