#include <Input.hpp>


Input::Input()
{
	for (int key = sf::Keyboard::A; key != sf::Keyboard::KeyCount; ++key)
	{
		sf::Keyboard::Key k = static_cast<sf::Keyboard::Key>(key);
		keyboardPressed[k] = false;
		keyboardReleased[k] = true;
		keyboardHold[k] = false;
	}
	for (int key = sf::Mouse::Left; key != sf::Mouse::ButtonCount; ++key)
	{
		sf::Mouse::Button b = static_cast<sf::Mouse::Button>(key);
		mousePressed[b] = false;
		mouseReleased[b] = true;
		mouseHold[b] = false;
	}
}

bool Input::isPressed(sf::Keyboard::Key key)
{
	return keyboardPressed[key];
}
bool Input::isPressed(sf::Mouse::Button key)
{
	return mousePressed[key];
}

bool Input::isReleased(sf::Keyboard::Key key)
{
	return keyboardReleased[key];
}
bool Input::isReleased(sf::Mouse::Button key)
{
	return mouseReleased[key];
}

bool Input::isHold(sf::Keyboard::Key key)
{
	return keyboardHold[key];
}
bool Input::isHold(sf::Mouse::Button key)
{
	return mouseHold[key];
}

bool Input::isHasFocus()
{
	return Engine::instance->m_window->hasFocus();
}

sf::Vector2f Input::getMousePosInWindow()
{
	/*auto window = Engine::instance->m_window;
	return window->mapPixelToCoords(sf::Mouse::getPosition(*window));*/
	return mousePosInWindow;
}

sf::Vector2f Input::getMousePosInWorld()
{
	return Engine::instance->m_window->mapPixelToCoords(sf::Vector2i(mousePosInWindow.x, mousePosInWindow.y));
}

float Input::getWheelDelta()
{
	return mouseWheelDelta;
}

void Input::Reset()
{
	for (int key = sf::Keyboard::A; key != sf::Keyboard::KeyCount; ++key)
	{
		sf::Keyboard::Key k = static_cast<sf::Keyboard::Key>(key);
		keyboardPressed[k] = false;
	}
	for (int key = sf::Mouse::Left; key != sf::Mouse::ButtonCount; ++key)
	{
		sf::Mouse::Button b = static_cast<sf::Mouse::Button>(key);
		mousePressed[b] = false;
	}
	mouseWheelDelta = 0;
}

void Input::Check(sf::Event& e)
{

	switch (e.type)
	{

	case sf::Event::KeyPressed:
		if (keyboardReleased[e.key.code])
		{
			keyboardPressed[e.key.code] = true;
			keyboardReleased[e.key.code] = false;
			keyboardHold[e.key.code] = true;
		}
		break;
	case sf::Event::KeyReleased:
		keyboardPressed[e.key.code] = false;
		keyboardReleased[e.key.code] = true;
		keyboardHold[e.key.code] = false;
		break;

	case sf::Event::MouseButtonPressed:
		if (mouseReleased[e.mouseButton.button])
		{
			mousePressed[e.mouseButton.button] = true;
			mouseReleased[e.mouseButton.button] = false;
			mouseHold[e.mouseButton.button] = true;
		}
		break;
	case sf::Event::MouseButtonReleased:
		mousePressed[e.mouseButton.button] = false;
		mouseReleased[e.mouseButton.button] = true;
		mouseHold[e.mouseButton.button] = false;
		break;
	case sf::Event::MouseWheelScrolled:
		mouseWheelDelta = e.mouseWheelScroll.delta;
		break;
	case sf::Event::MouseMoved:
		mousePosInWindow.x = e.mouseMove.x;
		mousePosInWindow.y = e.mouseMove.y;
		break;
	default:
		break;
	}


}


