#pragma once

#include <GameObject.hpp>
#include <Camera.hpp>

class Player : public GameObject
{
	Camera m_camera;
public:
	Player();
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	~Player() override = default;

	void Update() override;
	void Start() override;
};