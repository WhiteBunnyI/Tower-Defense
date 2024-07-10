#pragma once

#include <Engine.hpp>

class Camera : public IUpdateable
{
public:
	float speed;
	float sprintMul;

	Camera(float speed, float sprintMultiple);

	void Update() override;

	void SetPosition(sf::Vector2f pos);
};
