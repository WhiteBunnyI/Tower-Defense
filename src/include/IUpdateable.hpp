#pragma once

struct IUpdateable
{
	IUpdateable();
	virtual ~IUpdateable();
	virtual void Update() = 0;
};

