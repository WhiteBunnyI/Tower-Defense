#pragma once

struct IStartable
{
	IStartable();
	virtual ~IStartable();
	virtual void Start() = 0;
};