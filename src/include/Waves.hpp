#pragma once

#include <IUpdateable.hpp>
#include <SFML/Graphics.hpp>

class Waves : IUpdateable
{
	float timer;
	const float multiplyEnemys = 1.2f;
	int currentCount;
	sf::Texture* enemyTexture;
public:
	Waves();
	~Waves() override = default;

	void Update() override;
};