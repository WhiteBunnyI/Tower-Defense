#pragma once

#include <map>
#include <SFML/Graphics.hpp>

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

	sf::Vector2f mousePosInWindow;
	sf::Vector2f mousePosInWorld;
	float mouseWheelDelta;

public:
	Input();
	Input(const Input& other) = delete;
	Input& operator=(const Input& other) = delete;


	bool isPressed(sf::Keyboard::Key key);
	bool isPressed(sf::Mouse::Button key);

	bool isReleased(sf::Keyboard::Key key);
	bool isReleased(sf::Mouse::Button key);

	bool isHold(sf::Keyboard::Key key);
	bool isHold(sf::Mouse::Button key);

	bool isHasFocus();

	sf::Vector2f getMousePosInWindow();
	sf::Vector2f getMousePosInWorld();

	float getWheelDelta();

private:
	void Reset();
	void Check(sf::Event& e);
};

#include <Engine.hpp>