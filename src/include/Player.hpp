#pragma once

#include <GameObject.hpp>
#include <Camera.hpp>
#include <Input.hpp>
#include <Resources.hpp>
#include <Collision.hpp>

class Player : public GameObject
{
	enum class Tools
	{
		sword,
		pickaxe,
		axe,
	};

	float speed;
	float sprintMultiple;
	
	Camera m_camera;
	Input* input;
	GameObject sword;
	GameObject pickaxe;
	GameObject axe;
	GameObject statue;
	GameObject* currentToolObj;
	Tools currentTool;
	Collision::CircleCollider playerCollider;
	Collision::CircleCollider attackCollider;
	sf::Vector2f defaultToolPos;
	//sf::CircleShape* colliderShape;

	Resources resources;

	//Attack settings
	const float attackDur;
	const float attackRadius;
	//Attack variables
	bool isAttack;
	float attackTimer;
	float attackAngle;

public:
	Player(float speed, float sprintMultiple);
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	~Player() override = default;

	void ChangeTool();
	void Attack();
	void Move();

	void Update() override;
	void Start() override;
};