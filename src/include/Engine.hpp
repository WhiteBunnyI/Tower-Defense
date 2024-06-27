#pragma once

#include <GameObject.hpp>
#include <Coroutine.hpp>
#include <Vector2.hpp>
#include <MapGenerator.hpp>

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

	static inline Engine* instance{nullptr};

	MapGenerator map;

	std::list<GameObject> m_gameObjects;
	std::list<Coroutine> m_coroutines;
	std::list<sf::Drawable*> m_drawable;

	Engine();

	Engine(const Engine& engine) = delete;
	Engine& operator=(const Engine& other) = delete;

	void CrankUp(int gameWidth, int gameHeight);

	bool IsPlaying();
};



