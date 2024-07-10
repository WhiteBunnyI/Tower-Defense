#pragma once

#include <memory>

struct IUpdateable
{
	IUpdateable();
	virtual ~IUpdateable();
	virtual void Update() = 0;
};

