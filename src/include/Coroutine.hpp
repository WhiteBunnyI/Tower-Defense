#pragma once

class Coroutine
{
	float m_timer;
	void (*func)();

	friend class Engine;

	bool Tick(float deltaTime);

public:
	Coroutine(void (*func)(), float sec);

	void Start();

};

#include <Engine.hpp>

