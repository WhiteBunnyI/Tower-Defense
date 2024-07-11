#pragma once

#include <memory>

struct IUpdateable
{
	IUpdateable();
	virtual ~IUpdateable();
	virtual void Update() = 0;
};

struct ILateUpdateable
{
	ILateUpdateable();
	virtual ~ILateUpdateable();
	virtual void LateUpdate() = 0;
};
