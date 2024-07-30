#include <Player.hpp>
#include <Singleton.hpp>
#include <cmath>
#include <Deposit.hpp>

void ChangeVis(GameObject* obj)
{
	sf::Color color = obj->render->getColor();
	color.a = std::abs(color.a - 255);
	obj->render->setColor(color);
}

Player::Player(float speed, float sprintMultiple) :
	GameObject(),
	IHittable(100),
	speed{ speed },
	sprintMultiple{ sprintMultiple },
	input{ Engine::instance->m_input },
	currentToolObj{ &sword },
	attackRadius{ 1.f * Singleton::instance->map->m_texturesSize },
	isAttacking{ false },
	attackDur{ 0.25f },
	attackTimer{ 0 },
	attackAngle{ 0 },
	playerCollider{ this, render->getPosition(), 8 },
	attackTrigger{ this, sf::Vector2f(0,0), 3, true },
	isBuilding{ false }
{
	sf::Vector2f pos = Singleton::instance->map->getPlayerCoordsSpawn();
	m_camera.SetPosition(pos);
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("./resources/player/player.png");
	render->setOrigin(Singleton::instance->map->m_texturesSize / 2.f, Singleton::instance->map->m_texturesSize / 2.f);
	render->setTexture(*texture, true);
	render->setPosition(pos);

	defaultToolPos = sf::Vector2f(13, -4);

	sf::Texture* swordTexture = new sf::Texture();
	swordTexture->loadFromFile("./resources/player/sword.png");
	sword = GameObject(pos, swordTexture);
	sword.render->setOrigin(Singleton::instance->map->m_texturesSize / 2.f, Singleton::instance->map->m_texturesSize / 2.f);
	sword.render->setRotation(35);
	sword.render->setPosition(pos + defaultToolPos);

	sf::Texture* pickaxeTexture = new sf::Texture();
	pickaxeTexture->loadFromFile("./resources/player/pickaxe.png");
	pickaxe = GameObject(pos, pickaxeTexture);
	pickaxe.render->setOrigin(Singleton::instance->map->m_texturesSize / 2.f, Singleton::instance->map->m_texturesSize / 2.f);
	pickaxe.render->setRotation(35);
	pickaxe.render->setPosition(pos + defaultToolPos);

	sf::Texture* axeTexture = new sf::Texture();
	axeTexture->loadFromFile("./resources/player/axe.png");
	axe = GameObject(pos, axeTexture);
	axe.render->setOrigin(Singleton::instance->map->m_texturesSize / 2.f, Singleton::instance->map->m_texturesSize / 2.f);
	axe.render->setRotation(35);
	axe.render->setPosition(pos + defaultToolPos);
	
	ChangeVis(&pickaxe);
	ChangeVis(&axe);

	resourcesUI = new sf::Text();
	sf::Font* f = new sf::Font();
	f->loadFromFile("./resources/tuffy.ttf");
	resourcesUI->setFont(*f);
	resourcesUI->setCharacterSize(60);
	resourcesUI->setScale(0.2f, 0.2f);
	resourcesUI->setColor(sf::Color::Black);
	Engine::instance->m_manualRender.push_back(resourcesUI);

	ui_w_1 = new sf::RectangleShape();
	ui_w_2 = new sf::RectangleShape();
	ui_w_3 = new sf::RectangleShape();
	ui_keep = new sf::RectangleShape();
	ui_cave = new sf::RectangleShape();
	ui_lumber = new sf::RectangleShape();
	ui_archerBarrack = new sf::RectangleShape();
	ui_archer = new sf::RectangleShape();

	Engine::instance->m_manualRender.push_back(ui_w_1);
	Engine::instance->m_manualRender.push_back(ui_w_2);
	Engine::instance->m_manualRender.push_back(ui_w_3);
	Engine::instance->m_manualRender.push_back(ui_keep);
	Engine::instance->m_manualRender.push_back(ui_cave);
	Engine::instance->m_manualRender.push_back(ui_lumber);
	Engine::instance->m_manualRender.push_back(ui_archerBarrack);
	Engine::instance->m_manualRender.push_back(ui_archer);

	ui_w_1->setSize(sf::Vector2f(16, 16));
	ui_w_1->setTexture(&m_buildSystem.wall_1_t);

	ui_w_2->setSize(sf::Vector2f(16, 16));
	ui_w_2->setTexture(&m_buildSystem.wall_2_t);

	ui_w_3->setSize(sf::Vector2f(16, 16));
	ui_w_3->setTexture(&m_buildSystem.wall_3_t);

	ui_keep->setSize(sf::Vector2f(16, 16));
	ui_keep->setTexture(&m_buildSystem.keep_1);

	ui_cave->setSize(sf::Vector2f(16, 16));
	ui_cave->setTexture(&m_buildSystem.cave);

	ui_lumber->setSize(sf::Vector2f(16, 16));
	ui_lumber->setTexture(&m_buildSystem.lumber);

	ui_archerBarrack->setSize(sf::Vector2f(16, 16));
	ui_archerBarrack->setTexture(&m_buildSystem.archerBarrack);

	ui_archer->setSize(sf::Vector2f(16, 16));
	ui_archer->setTexture(&m_buildSystem.archer);

}

Player::~Player()
{
	Engine::instance->m_manualRender.remove(ui_w_1);
	Engine::instance->m_manualRender.remove(ui_w_2);
	Engine::instance->m_manualRender.remove(ui_w_3);
	Engine::instance->m_manualRender.remove(ui_keep);
	Engine::instance->m_manualRender.remove(ui_cave);
	Engine::instance->m_manualRender.remove(ui_lumber);
	Engine::instance->m_manualRender.remove(ui_archerBarrack);
	Engine::instance->m_manualRender.remove(ui_archer);

	delete ui_w_1; 
	delete ui_w_2; 
	delete ui_w_3; 
	delete ui_keep;
	delete ui_cave; 
	delete ui_lumber; 
	delete ui_archerBarrack; 
	delete ui_archer;
}

void Player::Start()
{
	

}


void Player::Update()
{
	if (input->isHasFocus())
	{
		Move();
		Attack();
		if (!isAttacking)
		{
			ChangeTool();
		}
		if (input->isPressed(sf::Keyboard::B))
		{
			isBuilding = !isBuilding;
			if (m_buildSystem.building != nullptr)
			{
				delete m_buildSystem.building;
				m_buildSystem.building = nullptr;
			}
		}
		if (isBuilding)
		{
			m_buildSystem.Build(input->getMousePosInWorld(), typeOfBuilding, input->isHold(sf::Mouse::Middle));
		}
	}
	playerCollider.Update(render->getPosition());
	
	UI();
	std::cout << " FPS: " << 1.f / Engine::instance->deltaTime << std::endl;
}

bool CheckUI(sf::RectangleShape* shape, sf::Vector2f mousePos)
{
	sf::Vector2f pos = shape->getPosition();
	sf::Vector2f scale = shape->getScale();
	if (mousePos.x >= pos.x && mousePos.x <= pos.x + scale.x * 16 && 
		mousePos.y >= pos.y && mousePos.y <= pos.y + scale.y * 16)
		return true;
	return false;
}

void Player::UI()
{
	sf::Vector2f viewSize = Engine::instance->m_view->getSize();
	sf::Vector2f pos = render->getPosition();


	std::string str("Wood: " + std::to_string(resource.resources[Resources::resource::wood]) +
		"\nIron: " + std::to_string(resource.resources[Resources::resource::iron]) +
		"\nGold: " + std::to_string(resource.resources[Resources::resource::gold]) +
		"\nRock: " + std::to_string(resource.resources[Resources::resource::rock]) +
		"\nArchers: " + std::to_string(resource.resources[Resources::resource::archer]));
	resourcesUI->setString(str);
	resourcesUI->setPosition(pos.x - viewSize.x / 2, pos.y - viewSize.y / 2);
	resourcesUI->setScale(viewSize.x / 2000, viewSize.y / 2000);

	ui_w_1->setScale(viewSize.x / 500, viewSize.y / 500);
	ui_w_1->setPosition(pos.x - viewSize.x / 2, pos.y + viewSize.y / 2 - viewSize.y / 500 * 17);

	ui_w_2->setScale(viewSize.x / 500, viewSize.y / 500);
	ui_w_2->setPosition(pos.x - viewSize.x / 2 + viewSize.x / 500 * 17, pos.y + viewSize.y / 2 - viewSize.y / 500 * 17);

	ui_w_3->setScale(viewSize.x / 500, viewSize.y / 500);
	ui_w_3->setPosition(pos.x - viewSize.x / 2 + 2 * viewSize.x / 500 * 17, pos.y + viewSize.y / 2 - viewSize.y / 500 * 17);

	ui_keep->setScale(viewSize.x / 500, viewSize.y / 500);
	ui_keep->setPosition(pos.x - viewSize.x / 2 + 3 * viewSize.x / 500 * 17, pos.y + viewSize.y / 2 - viewSize.y / 500 * 17);

	ui_cave->setScale(viewSize.x / 500, viewSize.y / 500);
	ui_cave->setPosition(pos.x - viewSize.x / 2 + 4 * viewSize.x / 500 * 17, pos.y + viewSize.y / 2 - viewSize.y / 500 * 17);

	ui_lumber->setScale(viewSize.x / 500, viewSize.y / 500);
	ui_lumber->setPosition(pos.x - viewSize.x / 2 + 5 * viewSize.x / 500 * 17, pos.y + viewSize.y / 2 - viewSize.y / 500 * 17);

	ui_archerBarrack->setScale(viewSize.x / 500, viewSize.y / 500);
	ui_archerBarrack->setPosition(pos.x - viewSize.x / 2 + 6 * viewSize.x / 500 * 17, pos.y + viewSize.y / 2 - viewSize.y / 500 * 17);

	ui_archer->setScale(viewSize.x / 500, viewSize.y / 500);
	ui_archer->setPosition(pos.x - viewSize.x / 2 + 7 * viewSize.x / 500 * 17, pos.y + viewSize.y / 2 - viewSize.y / 500 * 17);

	if (input->isPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = input->getMousePosInWorld();
		if (CheckUI(ui_w_1, mousePos))
		{
			typeOfBuilding = BuildSystem::Buildings::wall_1;
			return;
		}
		if (CheckUI(ui_w_2, mousePos))
		{
			typeOfBuilding = BuildSystem::Buildings::wall_2;
			return;
		}
		if (CheckUI(ui_w_3, mousePos))
		{
			typeOfBuilding = BuildSystem::Buildings::wall_3;
			return;
		}
		if (CheckUI(ui_keep, mousePos))
		{
			typeOfBuilding = BuildSystem::Buildings::keep_1;
			return;
		}
		if (CheckUI(ui_cave, mousePos))
		{
			typeOfBuilding = BuildSystem::Buildings::cave;
			return;
		}
		if (CheckUI(ui_lumber, mousePos))
		{
			typeOfBuilding = BuildSystem::Buildings::lumber;
			return;
		}
		if (CheckUI(ui_archerBarrack, mousePos))
		{
			typeOfBuilding = BuildSystem::Buildings::archerBarrack;
			return;
		}
		if (CheckUI(ui_archer, mousePos))
		{
			typeOfBuilding = BuildSystem::Buildings::archer;
			return;
		}
	}
}



void Player::ChangeTool()
{
	if (input->isPressed(sf::Keyboard::Num1))
	{
		ChangeVis(currentToolObj);

		currentToolObj = &sword;
		currentToolObj->render->setPosition(render->getPosition() + sf::Vector2f(13, -8));
		ChangeVis(currentToolObj);
	}
	else if (input->isPressed(sf::Keyboard::Num2))
	{
		ChangeVis(currentToolObj);

		currentToolObj = &pickaxe;
		currentToolObj->render->setPosition(render->getPosition() + defaultToolPos);
		ChangeVis(currentToolObj);
	}
	else if (input->isPressed(sf::Keyboard::Num3))
	{
		ChangeVis(currentToolObj);

		currentToolObj = &axe;
		currentToolObj->render->setPosition(render->getPosition() + defaultToolPos);
		ChangeVis(currentToolObj);
	}
}


void Player::Attack()
{
	//Начало атаки
	if (input->isPressed(sf::Mouse::Left))
	{
		if (!isAttacking)
		{
			isAttacking = true;
			attackTimer = 0;
			sf::Vector2f AB = input->getMousePosInWorld() - render->getPosition();

			float len = std::sqrtf(AB.x * AB.x + AB.y * AB.y);
			AB /= len;

			AB.x *= attackRadius;
			AB.y *= attackRadius;

			//0,523599 радиан = 30 градусам
			sf::Vector2f AC;
			AC.x = AB.x * std::cosf(-0.523599f) - AB.y * std::sinf(-0.523599f);
			AC.y = AB.x * std::sinf(-0.523599f) + AB.y * std::cosf(-0.523599f);

			attackAngle = std::atan2(AC.y, AC.x) * 180.f / 3.14f;

			currentToolObj->render->setPosition(AC + render->getPosition());
		}

	}
	if (isAttacking)
	{
		//Конец атаки
		if (attackTimer >= 1.f)
		{
			isAttacking = false;
			currentToolObj->render->setPosition(render->getPosition() + defaultToolPos);
			currentToolObj->render->setRotation(35);
			attackObj.clear();
			return;
		}
		//Атакуем
		
		//[0, 1] = [0, 60] градусов
			//std::cout << attackTimer << std::endl;
		float newAngle = attackAngle + 60.f * attackTimer;
		currentToolObj->render->setRotation(newAngle + 90);

		newAngle *= 3.14f / 180.f;
		sf::Vector2f newPos(render->getPosition().x + attackRadius * std::cosf(newAngle), render->getPosition().y + attackRadius * std::sinf(newAngle));

		currentToolObj->render->setPosition(newPos);
		attackTrigger.Update(newPos);

		attackTimer += Engine::instance->deltaTime / attackDur;

		std::list<Collision::BaseCollider*> p = Engine::instance->m_collision->getCollisions(&attackTrigger);
		if (!p.empty())
		{
			for (auto i : p)
			{
				//Уже атаковали этот объект
				if (attackObj.find(i->object) != attackObj.end())
					continue;

				if (dynamic_cast<Keep*>(i->object))
					continue;

				if (Deposit* dep = dynamic_cast<Deposit*>(i->object))
				{
					if (dep->type == Resources::resource::wood)
					{
						if (currentToolObj == &axe)
						{
							resource.resources[dep->type] += dep->Mine(3);	
						}
					}
					else
					{
						if (currentToolObj == &pickaxe)
						{
							resource.resources[dep->type] += dep->Mine(3);
						}
					}
					
					if (dep->IsDestroyed())
					{
						delete dep;
						continue;
					}
				}

				if (IHittable* d = dynamic_cast<IHittable*>(i->object))
				{
					if (currentToolObj == &sword)
					{
						if (d->Hit(5))
						{
							delete d;
							continue;
						}
					}
				}
				attackObj.insert(i->object);
			}
		}
	}
}

void Player::Move()
{
	auto map = Singleton::instance->map;
	Vector2 vec(0, 0);
	if (input->isHold(sf::Keyboard::S))
		vec.y += 1;
	if (input->isHold(sf::Keyboard::W))
		vec.y -= 1;
	if (input->isHold(sf::Keyboard::A))
		vec.x -= 1;
	if (input->isHold(sf::Keyboard::D))
		vec.x += 1;

	vec.Normalize();
	vec *= speed;
	if (input->isHold(sf::Keyboard::LShift))
		vec *= sprintMultiple;
	vec *= (float)Singleton::instance->map->m_texturesSize;
	vec *= Engine::instance->deltaTime;

	auto prediction = render->getPosition();
	sf::Vector2f currentGridCoords = map->CoordsToGridCoords(prediction);
	prediction.x += vec.x;
	prediction.y += vec.y;

	//currentGridCoords.x = std::rint(currentGridCoords.x);
	//currentGridCoords.y = std::rint(currentGridCoords.y);

	sf::Vector2f targetGridCoordsX(currentGridCoords);
	sf::Vector2f targetGridCoordsY(currentGridCoords);
	if (vec.x > 0)
		targetGridCoordsX.x += 0.5f;
	else if (vec.x < 0)
		targetGridCoordsX.x -= 0.5f;
	if (vec.y > 0)
		targetGridCoordsY.y += 0.5f;
	else if (vec.y < 0)
		targetGridCoordsY.y -= 0.5f;


	float tileSpeed = map->getTile(currentGridCoords.x, currentGridCoords.y)->speed;

	Tile* targetTileX = map->getTile(sf::Vector2i(targetGridCoordsX.x, targetGridCoordsX.y));
	Tile* targetTileY = map->getTile(sf::Vector2i(targetGridCoordsY.x, targetGridCoordsY.y));

	bool checkObjX = map->IsBuilding(targetGridCoordsX.x, targetGridCoordsX.y);
	bool checkObjY = map->IsBuilding(targetGridCoordsY.x, targetGridCoordsY.y);

	//std::cout << "Pos: " << (render->getPosition()).x << "," << (render->getPosition()).y << " | roundPos: " << currentGridCoords.x << "," << currentGridCoords.y << " | gridX: " << targetGridCoordsX.x << "," << targetGridCoordsX.y << " | roundGridX: " << std::floor(targetGridCoordsX.x) << "," << std::floor(targetGridCoordsX.y) << " | gridY: " << targetGridCoordsY.x << "," << targetGridCoordsY.y << " | roundGridY: " << std::floor(targetGridCoordsY.x) << "," << std::floor(targetGridCoordsY.y) << std::endl;

	//nullptr == выход за границы, speed = 0 == низя тут ходить
	if (targetTileX == nullptr || targetTileX->speed == 0 || checkObjX)
	{
		vec.x = 0;
	}

	if (targetTileY == nullptr || targetTileY->speed == 0 || checkObjY)
	{
		vec.y = 0;
	}
	m_camera.Move(sf::Vector2f(vec.x, vec.y));
	render->move(sf::Vector2f(vec.x, vec.y));
	currentToolObj->render->move(sf::Vector2f(vec.x, vec.y));

	float wheelDelta = input->getWheelDelta();
	if (wheelDelta != 0)
	{
		auto view = Engine::instance->m_view;
		m_camera.SetSize(view->getSize() - sf::Vector2f(16, 12) * wheelDelta);

	}

}

bool Player::Hit(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		std::cout << "Player dead\n";
		return true;
	}
	return false;
}

const BuildSystem& Player::getBuildSystem()
{
	return m_buildSystem;
}