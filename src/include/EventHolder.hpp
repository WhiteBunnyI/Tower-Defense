#pragma once

#include <SFML/Graphics.hpp>

struct EventHolder
{
	sf::Event::EventType eventType;
	sf::Keyboard listenButton;
	void (*func)();

	EventHolder(sf::Event::EventType eventType, sf::Keyboard onButton, void (*whatToCall)()) : eventType{ eventType }, listenButton{ onButton }, func{ whatToCall }
	{
		Engine::instance->m_events.push_back(this);
	}
};

#include <Engine.hpp>