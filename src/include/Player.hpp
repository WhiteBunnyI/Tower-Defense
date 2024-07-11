#pragma once

#include <GameObject.hpp>
#include <Camera.hpp>
#include <Mouse.hpp>

class Player : public GameObject
{
	float speed;
	float sprintMultiple;
	Camera m_camera;
	Mouse mouse;
public:
	Player(float speed, float sprintMultiple);
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	~Player() override = default;

	void Attack();

	void Update() override;
	void Start() override;
};