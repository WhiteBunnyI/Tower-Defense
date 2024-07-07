#include <Engine.hpp>

IUpdateable::IUpdateable()
{
	Engine::instance->m_update.push_back(this);
}

IUpdateable::~IUpdateable()
{
	Engine::instance->m_update.remove(this);
}

