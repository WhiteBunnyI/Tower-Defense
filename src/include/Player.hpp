#pragma once

#include <GameObject.hpp>
#include <Camera.hpp>
#include <Input.hpp>

class Player : public GameObject
{
	float speed;
	float sprintMultiple;
	Camera m_camera;
	Input* input;
	GameObject sword;
	GameObject pickaxe;
	GameObject axe;

public:
	Player(float speed, float sprintMultiple);
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	~Player() override = default;

	void Attack();
	void Move();

	void Update() override;
	void Start() override;
};