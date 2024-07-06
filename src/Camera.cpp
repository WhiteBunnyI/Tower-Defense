#include <Camera.hpp>

void Camera::Update()
{
	auto view = Engine::instance->m_view;
	auto window = Engine::instance->m_window;

	Vector2 vec(0, 0);
	if (m_down)
		vec.y += speed;
	if (m_up)
		vec.y -= speed;
	if (m_left)
		vec.x -= speed;
	if (m_right)
		vec.x += speed;

	view->move(vec.x, vec.y);
	window->setView(*view);
}
