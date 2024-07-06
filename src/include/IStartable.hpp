#pragma once

struct IStartable
{
	IStartable();
	virtual void Start() = 0;
};