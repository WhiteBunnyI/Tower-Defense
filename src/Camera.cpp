#include <Camera.hpp>
#include <Engine.hpp>

void Camera::SetPosition(sf::Vector2f pos)
{
	Engine::instance->m_view->setCenter(pos);
	Engine::instance->UpdateView();
}
void Camera::Move(sf::Vector2f vector)
{
	Engine::instance->m_view->move(vector);
	Engine::instance->UpdateView();
}
void Camera::Move(float offsetX, float offsetY)
{
	Engine::instance->m_view->move(offsetX, offsetY);
	Engine::instance->UpdateView();
}