#pragma once

#include <IUpdateable.hpp>

class Waves : IUpdateable
{
	float timer;
	const float multiplyEnemys = 1.2f;
	int currentCount;
public:
	Waves();
	~Waves() override = default;

	void Update() override;
};