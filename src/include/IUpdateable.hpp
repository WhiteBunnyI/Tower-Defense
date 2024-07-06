#pragma once

struct IUpdateable
{
	IUpdateable();
	virtual void Update() = 0;
};

