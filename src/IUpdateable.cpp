#include <Engine.hpp>

IUpdateable::IUpdateable()
{
	Engine::instance->m_update.push_back(this);
}
