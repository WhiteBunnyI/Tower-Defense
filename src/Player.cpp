#include <Player.hpp>
#include <Singleton.hpp>
#include <cmath>

void ChangeVis(GameObject* obj)
{
	sf::Color color = obj->render->getColor();
	color.a = std::abs(color.a - 255);
	obj->render->setColor(color);
}

Player::Player(float speed, float sprintMultiple) : 
	GameObject(),
	speed{ speed },
	sprintMultiple{ sprintMultiple },
	input{ Engine::instance->m_input },
	currentTool{ Tools::sword },
	currentToolObj{ &sword },
	attackRadius{ 1.f * Singleton::instance->map->m_texturesSize },
	isAttack{ false },
	attackDur{ 0.25f },
	attackTimer{ 0 },
	attackAngle{ 0 },
	playerCollider{ this, render->getPosition(), 8 },
	attackCollider{ &sword, sf::Vector2f(0,0), 3 }
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
	sword = GameObject(pos, swordTexture, true);
	sword.render->setOrigin(Singleton::instance->map->m_texturesSize / 2.f, Singleton::instance->map->m_texturesSize / 2.f);
	sword.render->setRotation(35);
	sword.render->setPosition(pos + defaultToolPos);

	sf::Texture* pickaxeTexture = new sf::Texture();
	pickaxeTexture->loadFromFile("./resources/player/pickaxe.png");
	pickaxe = GameObject(pos, pickaxeTexture, true);
	pickaxe.render->setOrigin(Singleton::instance->map->m_texturesSize / 2.f, Singleton::instance->map->m_texturesSize / 2.f);
	pickaxe.render->setRotation(35);
	pickaxe.render->setPosition(pos + defaultToolPos);

	sf::Texture* axeTexture = new sf::Texture();
	axeTexture->loadFromFile("./resources/player/axe.png");
	axe = GameObject(pos, axeTexture, true);
	axe.render->setOrigin(Singleton::instance->map->m_texturesSize / 2.f, Singleton::instance->map->m_texturesSize / 2.f);
	axe.render->setRotation(35);
	axe.render->setPosition(pos + defaultToolPos);

	sf::Texture* statueTexture = new sf::Texture();
	statueTexture->loadFromFile("./resources/player/statue.png");
	statue = GameObject(pos, statueTexture, true);
	statue.render->setOrigin(Singleton::instance->map->m_texturesSize / 2.f, Singleton::instance->map->m_texturesSize);
	statue.render->setPosition(pos);
	ChangeVis(&pickaxe);
	ChangeVis(&axe);

	//colliderShape = new sf::CircleShape();
	//colliderShape->setRadius(8);
	//colliderShape->setFillColor(sf::Color::Transparent);
	//colliderShape->setOutlineThickness(1);
	//colliderShape->setOutlineColor(sf::Color::Magenta);
	//colliderShape->setOrigin(8, 8);
	//Engine::instance->m_manualRender.push_back(colliderShape);
}

void Player::Start()
{
	

}


void Player::Update()
{
	//colliderShape->setPosition(render->getPosition());
	if (input->isHasFocus())
	{
		Move();
		Attack();
		if (!isAttack)
		{
			ChangeTool();
		}
	}
	playerCollider.Update(render->getPosition());
}


void Player::ChangeTool()
{
	if (input->isPressed(sf::Keyboard::Num1))
	{
		ChangeVis(currentToolObj);

		currentTool = Tools::sword;
		currentToolObj = &sword;
		currentToolObj->render->setPosition(render->getPosition() + sf::Vector2f(13, -8));
		ChangeVis(currentToolObj);
	}
	else if (input->isPressed(sf::Keyboard::Num2))
	{
		ChangeVis(currentToolObj);

		currentTool = Tools::pickaxe;
		currentToolObj = &pickaxe;
		currentToolObj->render->setPosition(render->getPosition() + defaultToolPos);
		ChangeVis(currentToolObj);
	}
	else if (input->isPressed(sf::Keyboard::Num3))
	{
		ChangeVis(currentToolObj);

		currentTool = Tools::axe;
		currentToolObj = &axe;
		currentToolObj->render->setPosition(render->getPosition() + defaultToolPos);
		ChangeVis(currentToolObj);
	}
}


void Player::Attack()
{
	if (input->isPressed(sf::Mouse::Left))
	{
		if (!isAttack)
		{
			std::cout << "ATTACK" << std::endl;
			isAttack = true;
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

			std::cout << attackAngle << std::endl;

			currentToolObj->render->setPosition(AC + render->getPosition());
		}

	}
	if (isAttack)
	{
		if (attackTimer >= 1.f)
		{
			isAttack = false;
			currentToolObj->render->setPosition(render->getPosition() + defaultToolPos);
			currentToolObj->render->setRotation(35);
		}
		else
		{
			//[0, 1] = [0, 60] градусов
			//std::cout << attackTimer << std::endl;
			float newAngle = attackAngle + 60.f * attackTimer;
			currentToolObj->render->setRotation(newAngle + 90);

			newAngle *= 3.14f / 180.f;
			sf::Vector2f newPos(render->getPosition().x + attackRadius * std::cosf(newAngle), render->getPosition().y + attackRadius * std::sinf(newAngle));

			currentToolObj->render->setPosition(newPos);
			attackCollider.Update(newPos);

			attackTimer += Engine::instance->deltaTime / attackDur;

			std::list<Collision::BaseCollider*> p = Engine::instance->m_collision->getCollisions(&attackCollider);

			if (!p.empty())
			{
				for (auto i : p)
				{
					std::cout << "Пересекает: " << i->center.x << "," << i->center.y << std::endl;
				}
			}
		}
	}
}

void Player::Move()
{
	auto map = Singleton::instance->map;
	sf::Vector2f vec(0, 0);
	if (input->isHold(sf::Keyboard::S))
		vec.y += speed;
	if (input->isHold(sf::Keyboard::W))
		vec.y -= speed;
	if (input->isHold(sf::Keyboard::A))
		vec.x -= speed;
	if (input->isHold(sf::Keyboard::D))
		vec.x += speed;
	if (input->isHold(sf::Keyboard::LShift))
		vec *= sprintMultiple;

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

	Tile* targetTileX = map->getTile(sf::Vector2i(std::floor(targetGridCoordsX.x), std::floor(targetGridCoordsX.y)));
	Tile* targetTileY = map->getTile(sf::Vector2i(std::floor(targetGridCoordsY.x), std::floor(targetGridCoordsY.y)));

	//std::cout << "Pos: " << (render->getPosition()).x << "," << (render->getPosition()).y << " | roundPos: " << currentGridCoords.x << "," << currentGridCoords.y << " | gridX: " << targetGridCoordsX.x << "," << targetGridCoordsX.y << " | roundGridX: " << std::floor(targetGridCoordsX.x) << "," << std::floor(targetGridCoordsX.y) << " | gridY: " << targetGridCoordsY.x << "," << targetGridCoordsY.y << " | roundGridY: " << std::floor(targetGridCoordsY.x) << "," << std::floor(targetGridCoordsY.y) << std::endl;

	//nullptr == выход за границы, speed = 0 == низя тут ходить
	if (targetTileX == nullptr || targetTileX->speed == 0)
	{
		vec.x = 0;
	}

	if (targetTileY == nullptr || targetTileY->speed == 0)
	{
		vec.y = 0;
	}
	m_camera.Move(vec);
	render->move(vec);
	currentToolObj->render->move(vec);

	float wheelDelta = input->getWheelDelta();
	if (wheelDelta != 0)
	{
		auto view = Engine::instance->m_view;
		m_camera.SetSize(view->getSize() - sf::Vector2f(16, 12) * wheelDelta);

	}

}