#pragma once

struct IStartable
{
	friend class Engine;
	IStartable();
	virtual ~IStartable();
protected:
	virtual void Start() = 0;
};