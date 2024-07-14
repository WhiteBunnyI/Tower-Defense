#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>

#include <Input.hpp>
#include <Vector2.hpp>
#include <IUpdateable.hpp>
#include <IStartable.hpp>
#include <IRenderable.hpp>
#include <GameObject.hpp>
#include <Coroutine.hpp>
#include <MapGenerator.hpp>
#include <EventHolder.hpp>
#include <ThreadPool.hpp>
#include <Collision.hpp>

class Engine
{
	bool isPlaying = false;
public:
	static inline Engine* instance{nullptr};
	float deltaTime;
	int m_gameWidth; 
	int m_gameHeight;

	my::ThreadPool threadPool;
	Collision m_collision;
	Input* m_input;

	sf::View* m_view;
	sf::RenderWindow* m_window;

	std::list<IStartable*> m_start;
	std::list<IUpdateable*> m_update;
	std::list<ILateUpdateable*> m_lateUpdate;
	std::list<IRenderable*> m_render;
	std::list<sf::Drawable*> m_manualRender;

	std::list<BaseCoroutine*> m_coroutines;
	std::list<BaseEventHolder*> m_events;
	std::list<sf::Texture*> m_textures;

	Engine(int gameWidth, int gameHeight, sf::Vector2i gridSizeCollision, sf::Vector2i mapSize);
	Engine(const Engine& engine) = delete;
	Engine& operator=(const Engine& other) = delete;
	~Engine();

	template<typename T>
	static void ClearList(std::list<T>& lst)
	{
		for (auto iter = lst.begin(); iter != lst.end(); ++iter)
		{
			delete (*iter);
		}
		lst.clear();
	}

	void CrankUp();

	bool IsPlaying();

	void UpdateView();
};



