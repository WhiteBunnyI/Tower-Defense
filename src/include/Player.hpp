#pragma once

#include <GameObject.hpp>
#include <Camera.hpp>

class Player : public GameObject
{
	float speed;
	float sprintMultiple;
	Camera m_camera;
public:
	Player(float speed, float sprintMultiple);
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	~Player() override = default;

	void Update() override;
	void Start() override;
};