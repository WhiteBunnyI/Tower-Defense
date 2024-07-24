#include <Enemy.hpp>
#include <Engine.hpp>
#include <Singleton.hpp>

using Node = my::pathFinding::Node;
using PathFinding = my::pathFinding::PathFinding;


Enemy::Enemy(const sf::Vector2f position, sf::Texture* texture, int health, int damage, float moveSpeed, float attackCooldown) :
	GameObject(position, texture),
	IHittable(health),
	isDead{ false },
	isCalculatingPath{ false },
	collider{ this, position, 4 },
	attackTrigger{ this, position, 6, true },
	speed{ moveSpeed },
	attackCooldown{ attackCooldown },
	attackTimer{ 0 },
	moveTimer{ 0 },
	currentPosTarget(-1, -1),
	currentPos{ position },
	damage{ damage }
{
	render->setOrigin(8, 8);
	calculateFunc = [this]()
		{
			Vector2I current;
			if (currentPosTarget.x > -1 && currentPosTarget.y > -1)
				current = Vector2I(currentPosTarget.x, currentPosTarget.y);
			else
				current = Vector2I(currentPos.x, currentPos.y);

			Node* temp;
			sf::Vector2f dist(playerPos.x - current.x, playerPos.y - current.y);

			if (std::sqrt(dist.x * dist.x + dist.y * dist.y) <= 35)
				temp = finder.CalculatePath(current, Vector2I(playerPos.x, playerPos.y), 1);
			else
				temp = finder.CalculatePath(current, Vector2I(playerPos.x, playerPos.y), 0.5f);

			std::forward_list<sf::Vector2i> lst;
			if (temp != nullptr)
			{
				while (temp->parent != nullptr)
				{
					lst.push_front(sf::Vector2i(temp->pos.x, temp->pos.y));
					temp = temp->parent;
				}
			}
			{
				std::unique_lock<std::mutex> lock(m);
				isCalculatingPath = false;
				std::swap(lst, path);
			}
		};
}


void Enemy::Start()
{

}

bool Enemy::Hit(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		return true;
	}
	return false;
}

#ifdef DEBUG_PATHFINDING

void DrawLine(Vector2I a, Vector2I b)
{
	sf::RectangleShape* line = new sf::RectangleShape();
	MapGenerator* map = Singleton::instance->map;
	float dx = (b.x - a.x) * map->m_texturesSize;
	float dy = (b.y - a.y) * map->m_texturesSize;
	float dist = std::sqrtf(dx * dx + dy * dy);
	line->setSize(sf::Vector2f(dist, map->m_texturesSize / 4));
	line->setFillColor(sf::Color::Black);
	line->setOrigin(0, map->m_texturesSize / 8);
	line->setPosition((map->GridCoordsToCenterCoords(a.x, a.y)));
	float angle = std::atan2(dy, dx) * (180.f/3.14f);
	line->rotate(angle);
	Engine::instance->m_manualRender.push_back(line);
}

void DrawPath(std::forward_list<sf::Vector2i> lst)
{
	Vector2I a(-1,-1);
	for (auto iter = lst.begin(); iter != lst.end(); ++iter)
	{
		Vector2I b(iter->x, iter->y);
		if (a != Vector2I(-1, -1))
		{
			DrawLine(a, b);
		}
		a = b;
	}
}

#endif // DEBUG_PATHFINDING

void Enemy::Attack()
{
	if (attackTimer <= 0)
	{
		std::list<Collision::BaseCollider*> collisions = Engine::instance->m_collision->getCollisions(&attackTrigger);
		if (!collisions.empty())
		{
			for (auto i : collisions)
			{
				if (i->isTrigger || i->object == this || dynamic_cast<Enemy*>(i->object))
					continue;
				
				if (Singleton::instance->player == i->object)
				{
					attackTimer = attackCooldown;
					if (Singleton::instance->player->Hit(damage))
					{

					}
					continue;
				}

				else if (IHittable* d = dynamic_cast<IHittable*>(i->object))
				{
					attackTimer = attackCooldown;
					if (d->Hit(damage))
					{
						auto p = Singleton::instance->map->CoordsToGridCoords(i->object->render->getPosition());
						Singleton::instance->map->getObj(p.x, p.y) = nullptr;
						delete d;
					}
				}
			}
		}
	}
}

void Enemy::Attack(int x, int y)
{
	if (attackTimer <= 0)
	{
		if (!Singleton::instance->map->IsBuilding(x, y))
			return;
		GameObject* g = Singleton::instance->map->getObj(x, y);
		if (g != nullptr)
		{
			if (IHittable* d = dynamic_cast<IHittable*>(g))
			{
				attackTimer = attackCooldown;
				if (d->Hit(damage))
				{
					Singleton::instance->map->getObj(x, y) = nullptr;
					delete d;
				}
			}
			
		}
	}
}

void Enemy::Update()
{
	if (isDead)
		return;

	MapGenerator* map = Singleton::instance->map;
	Player* player = Singleton::instance->player;

	
	attackTimer -= Engine::instance->deltaTime;
	Attack();
	if (!isCalculatingPath && currentPosTarget == sf::Vector2i(-1, -1) || moveTimer >= 1)
	{
		std::unique_lock<std::mutex> lock(m);
		if (!path.empty())
		{
			moveTimer = 0;
			startPos = render->getPosition();
			currentPosTarget = path.front();
			path.pop_front();
		}
	}

	if (currentPosTarget != sf::Vector2i(-1, -1))
	{
		if (moveTimer >= 1)
			moveTimer = 1;
		if (map->IsBuilding(currentPosTarget.x, currentPosTarget.y))
		{
			Attack(currentPosTarget.x, currentPosTarget.y);
			return;
		}
		sf::Vector2f targetPos = map->GridCoordsToCenterCoords(currentPosTarget.x, currentPosTarget.y);
		float tileSpeed = Tile::MoveSpeed(map->getTile(currentPosTarget)->type);

		render->setPosition((targetPos - startPos) * moveTimer + startPos);

		moveTimer += Engine::instance->deltaTime * tileSpeed * speed;
	}

	std::function<void()> customFunc = [this]()
		{
			std::this_thread::sleep_for(std::chrono::microseconds(200));
			std::cout << "End\n";
			{
				std::unique_lock<std::mutex> lock(m);
				isCalculatingPath = false;
			}
		};

	if (!isCalculatingPath)
	{
		sf::Vector2f playerPosInGrid;
		if (player->getBuildSystem().buildLevel == 0)
			playerPosInGrid = map->CoordsToGridCoords(player->render->getPosition());
		else
			playerPosInGrid = map->CoordsToGridCoords(player->getBuildSystem().keepObj->render->getPosition());

		if (playerPos != playerPosInGrid)
		{
			currentPos = map->CoordsToGridCoords(render->getPosition());
			playerPos = playerPosInGrid;
			isCalculatingPath = true;
			//Engine::instance->threadPool->enqueue(customFunc);
			Engine::instance->threadPool->enqueue(calculateFunc);
			//calculateFunc();
		}
	}
	collider.Update(render->getPosition());
	attackTrigger.Update(collider.center);
}

void Enemy::LateUpdate()
{
#ifdef DEBUG_PATHFINDING
	if (isDead)
		return;
	


	if (Engine::instance->m_input->isPressed(sf::Keyboard::C))
	{
		DrawPath(path);
	}

	if (Engine::instance->m_input->isPressed(sf::Keyboard::Space))
	{
		for (auto i : tempList)
		{
			Engine::instance->m_manualRender.remove(i);
			delete i;
		}
		tempList.clear();
		auto checked = finder.checked;
		auto awaits = finder.awaits;
		sf::RectangleShape* shape;
		for (auto i : checked)
		{
			shape = new sf::RectangleShape();
			tempList.push_back(shape);
			sf::Color color(sf::Color::Black);
			color.a = 155;
			shape->setFillColor(color);
			//shape->setOrigin(8, 8);
			shape->setSize(sf::Vector2f(16, 16));
			shape->setPosition(sf::Vector2f(i->pos.x * 16, i->pos.y * 16));
			std::cout << (i->pos.x * 16) << " / " << Singleton::instance->player->render->getPosition().x << std::endl;
			Engine::instance->m_manualRender.push_back(shape);

		}
		for (auto i : awaits)
		{
			shape = new sf::RectangleShape();
			tempList.push_back(shape);
			sf::Color color(sf::Color::White);
			color.a = 155;
			shape->setFillColor(color);
			//shape->setOrigin(8, 8);
			shape->setSize(sf::Vector2f(16, 16));
			shape->setPosition(sf::Vector2f(i->pos.x * 16, i->pos.y * 16));
			Engine::instance->m_manualRender.push_back(shape);
		}
	}


#endif // DEBUG_PATHFINDING
}