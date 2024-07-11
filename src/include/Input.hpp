#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>

class Input
{
private:
	
	friend class Engine;
	std::map<sf::Keyboard::Key, bool> keyboardPressed;
	std::map<sf::Keyboard::Key, bool> keyboardReleased;
	std::map<sf::Keyboard::Key, bool> keyboardHold;
	std::map<sf::Mouse::Button, bool> mousePressed;
	std::map<sf::Mouse::Button, bool> mouseReleased;
	std::map<sf::Mouse::Button, bool> mouseHold;


public:
	Input()
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
	Input(const Input& other) = delete;
	Input& operator=(const Input& other) = delete;


	bool isPressed(sf::Keyboard::Key key)
	{
		return keyboardPressed[key];
	}
	bool isPressed(sf::Mouse::Button key)
	{
		return mousePressed[key];
	}

	bool isReleased(sf::Keyboard::Key key)
	{
		return keyboardReleased[key];
	}
	bool isReleased(sf::Mouse::Button key)
	{
		return mouseReleased[key];
	}

	bool isHold(sf::Keyboard::Key key)
	{
		return keyboardHold[key];
	}
	bool isHold(sf::Mouse::Button key)
	{
		return mouseHold[key];
	}

	bool isHasFocus()
	{
		return Engine::instance->m_window->hasFocus();
	}

	sf::Vector2f getMousePos()
	{
		auto window = Engine::instance->m_window;
		return window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	}

private:
	void Check(sf::Event& e)
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
		default:
			break;
		}


	}
	void Reset()
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
	}
};

#include <Engine.hpp>