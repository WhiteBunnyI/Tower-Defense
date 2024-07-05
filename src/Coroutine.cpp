#include <Coroutine.hpp>

bool Coroutine::Tick(float deltaTime)
{
	m_timer -= deltaTime;

	if (m_timer <= 0.f)
	{
		func();
		return true;
	}
	return false;
}

Coroutine::Coroutine(void (*func)(), float sec)
{
	this->func = func;
	m_timer = sec;
}


void Coroutine::Start()
{
	Engine::instance->m_coroutines.push_back(this);
}

