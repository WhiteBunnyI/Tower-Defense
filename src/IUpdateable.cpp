#include <IUpdateable.hpp>
#include <Engine.hpp>

IUpdateable::IUpdateable()
{
	Engine::instance->m_update.push_back(this);
}

IUpdateable::~IUpdateable()
{
	Engine::instance->m_update.remove(this);
}

ILateUpdateable::ILateUpdateable()
{
	Engine::instance->m_lateUpdate.push_back(this);
}

ILateUpdateable::~ILateUpdateable()
{
	Engine::instance->m_lateUpdate.remove(this);
}