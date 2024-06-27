#pragma once

#include <Vector2.hpp>

class IPlaceable
{
public:
	virtual void Place(Vector2 at) = 0;
};