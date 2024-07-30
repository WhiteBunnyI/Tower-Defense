#pragma once

#include <GameObject.hpp>
#include <Camera.hpp>
#include <Input.hpp>
#include <Resources.hpp>
#include <Collision.hpp>
#include <IHittable.hpp>
#include <Keep.hpp>
#include <unordered_set>
#include <Building.hpp>

class Player : public GameObject, public IHittable
{
	float speed;
	float sprintMultiple;
	
	Camera m_camera;
	Input* input;

	BuildSystem m_buildSystem;
	BuildSystem::Buildings typeOfBuilding = BuildSystem::Buildings::wall_1;
	bool isBuilding;

	GameObject sword;
	GameObject pickaxe;
	GameObject axe;
	GameObject* currentToolObj;

	Collision::CircleCollider playerCollider;
	Collision::CircleCollider attackTrigger;
	sf::Vector2f defaultToolPos;
	
	//UI

	sf::Text* resourcesUI;

	sf::RectangleShape* ui_w_1;
	sf::RectangleShape* ui_w_2;
	sf::RectangleShape* ui_w_3;
	sf::RectangleShape* ui_keep;
	sf::RectangleShape* ui_cave;
	sf::RectangleShape* ui_lumber;
	sf::RectangleShape* ui_archerBarrack;
	sf::RectangleShape* ui_archer;

	//Attack settings

	const float attackDur;
	const float attackRadius;

	//Attack variables

	bool isAttacking;
	float attackTimer;
	float attackAngle;
	std::unordered_set<GameObject*> attackObj;
protected:

	void Update() override;
	void Start() override;

public:
	Resources resource;

	Player(float speed, float sprintMultiple);
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	~Player() override;

	void ChangeTool();
	void Attack();
	void Move();
	void UI();
	bool Hit(int damage) override;

	const BuildSystem& getBuildSystem();
};