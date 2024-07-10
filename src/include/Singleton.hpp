#pragma once

#include <MapGenerator.hpp>
#include <Player.hpp>

struct Singleton
{
	static inline Singleton* instance{ nullptr };
	MapGenerator* map;
	Player* player;

	Singleton() : map{nullptr}, player{nullptr}
	{
		if (instance != nullptr)
		{
			std::cerr << "Singleton already exist!" << std::endl;
			throw new std::runtime_error("Singleton already exist!");
		}
		instance = this;
	}
};