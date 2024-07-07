#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>

#include <Vector2.hpp>
#include <IUpdateable.hpp>
#include <IStartable.hpp>
#include <IRenderable.hpp>
#include <GameObject.hpp>
#include <Coroutine.hpp>
#include <MapGenerator.hpp>
#include <EventHolder.hpp>

class Engine
{
	bool isPlaying = false;
public:
	float deltaTime;
	int m_gameWidth; 
	int m_gameHeight;
	sf::View* m_view;
	sf::RenderWindow* m_window;
	static inline Engine* instance{nullptr};

	std::list<IUpdateable*> m_update;
	std::list<IStartable*> m_start;
	std::list<IRenderable*> m_render;
	std::list<sf::Drawable*> m_manualRender;

	std::list<BaseCoroutine*> m_coroutines;
	std::list<BaseEventHolder*> m_events;

	Engine(int gameWidth, int gameHeight);
	~Engine();
	Engine(const Engine& engine) = delete;
	Engine& operator=(const Engine& other) = delete;

	void CrankUp();

	bool IsPlaying();

	void UpdateView();
};



