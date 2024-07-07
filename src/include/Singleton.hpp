#pragma once

#include <MapGenerator.hpp>

struct Singleton
{
	static inline Singleton* instance{ nullptr };
	MapGenerator* map;

	Singleton() : map{nullptr}
	{
		if (instance != nullptr)
		{
			std::cerr << "Singleton already exist!" << std::endl;
			throw new std::runtime_error("Singleton already exist!");
		}
		instance = this;
	}
};