#pragma once

#include <GameObject.hpp>
#include <Coroutine.hpp>
#include <Vector2.hpp>
#include <MapGenerator.hpp>
#include <EventHolder.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>

class Engine
{
	bool isPlaying = false;
public:
	int m_gameWidth; 
	int m_gameHeight;
	sf::View* m_view;
	static inline Engine* instance{nullptr};

	std::list<GameObject*> m_gameObjects;
	std::list<Coroutine*> m_coroutines;
	std::list<EventHolder*> m_events;

	Engine(int gameWidth, int gameHeight);

	Engine(const Engine& engine) = delete;
	Engine& operator=(const Engine& other) = delete;

	void CrankUp();

	bool IsPlaying();
};



