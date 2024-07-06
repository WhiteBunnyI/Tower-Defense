#include <Engine.hpp>

IStartable::IStartable()
{
	Engine::instance->m_start.push_back(this);
}
