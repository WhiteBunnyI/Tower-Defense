#include <Waves.hpp>
#include <Engine.hpp>
#include <Enemy.hpp>

Waves::Waves() : IUpdateable(), currentCount{5}, timer{60}
{
	
}

void Waves::Update()
{
	timer -= Engine::instance->deltaTime;
	if (timer <= 0)
	{
		timer = 60;

		for (int i = 0; i < currentCount; i++)
		{

		}

		currentCount *= multiplyEnemys;
	}
}