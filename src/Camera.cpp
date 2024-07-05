#include <Camera.hpp>

void Camera::Move(Vector2 newPos)
{
	Engine::instance->m_view->move(newPos.x, newPos.y);
}