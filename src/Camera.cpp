#include <Camera.hpp>

void Camera::Update()
{
	auto view = Engine::instance->m_view;
	auto window = Engine::instance->m_window;

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
	window->setView(*view);
}
