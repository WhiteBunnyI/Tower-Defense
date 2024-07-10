#include <Camera.hpp>

Camera::Camera(float speed, float sprintMultiple) : IUpdateable(), speed{ speed }, sprintMul{ sprintMultiple } {}

void Camera::SetPosition(sf::Vector2f pos)
{
	auto view = Engine::instance->m_view;
	view->setCenter(pos);
	Engine::instance->UpdateView();
}

void Camera::Update()
{
	auto view = Engine::instance->m_view;

	Vector2 vec(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		vec.y += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		vec.y -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		vec.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		vec.x += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		vec *= sprintMul;

	vec *= Engine::instance->deltaTime;

	view->move(vec.x, vec.y);
	Engine::instance->UpdateView();
}
