#pragma once

#include <Coroutine.hpp>

class Mouse : IUpdateable
{

public:
	bool timer;

	Mouse();

	void Update() override;

};

#include <Engine.hpp>
