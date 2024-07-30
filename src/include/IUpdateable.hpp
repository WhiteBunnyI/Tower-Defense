#pragma once

struct IUpdateable
{
	friend class Engine;
	IUpdateable();
	virtual ~IUpdateable();
protected:
	virtual void Update() = 0;
};

struct ILateUpdateable
{
	friend class Engine;
	ILateUpdateable();
	virtual ~ILateUpdateable();
protected:
	virtual void LateUpdate() = 0;
};
