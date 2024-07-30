#include <Building.hpp>
#include <Singleton.hpp>
#include <Engine.hpp>
#include <Deposit.hpp>

Building::Archer::Archer(const sf::Vector2f position, sf::Texture* texture, int health) :
	GameObject(position, texture),
	IHittable(health),
	collider{ this, position, 6 },
	attackTrigger{ this, position, 64, true } {}

bool Building::Archer::Hit(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
		return true;
	return false;
}

Building::Wall::Wall(const sf::Vector2f position, sf::Texture* texture, int health) :
	GameObject(position, texture),
	IHittable(health),
	archer{ nullptr },
	collider{ this, position, 4 } {}

Building::Wall::~Wall()
{
	if (archer != nullptr)
		delete archer;
}

bool Building::Wall::PlaceArcher(sf::Texture& texture)
{
	if (archer != nullptr)
		return false;
	archer = new Building::Archer(render->getPosition(), &texture, 100000);
	archer->collider.radius = 0;
	return true;
}

bool Building::Wall::Hit(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		return true;
	}
	return false;
}

Building::WorkStation::WorkStation(const sf::Vector2f position, sf::Texture* texture, int health) :
	GameObject(position, texture),
	IHittable{ health },
	gatherCollider{ this, position, 24, true },
	isWorking{ false },
	m_resourcesPer15sec{ 0 },
	m_timer{ 0 },
	m_typeOfResource{ Resources::resource::nothing },
	collider{ this, position, 4 } {}

Building::WorkStation::WorkStation(const sf::Vector2f position, sf::Texture* texture, int health, Resources::resource typeOfResource, int resourcesPer15sec) :
	GameObject(position, texture),
	IHittable{ health },
	m_typeOfResource{ typeOfResource },
	m_resourcesPer15sec{ resourcesPer15sec },
	m_timer{ 0 },
	gatherCollider{ this, position, 0, true },
	isWorking{ false },
	collider{ this, position, 4 } {}

void Building::WorkStation::Update()
{
	if (!isWorking)
		return;
	m_timer += Engine::instance->deltaTime;
	if (m_timer >= 15)
	{
		m_timer = 0;
		Singleton::instance->player->resource.resources[m_typeOfResource] += m_resourcesPer15sec;
	}
}

bool Building::WorkStation::Hit(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
		return true;
	return false;
}


GameObject* BuildSystem::getGameObjectInGrid(sf::Vector2f pos)
{
	return getGameObjectInGrid(pos.x, pos.y);
}

GameObject* BuildSystem::getGameObjectInGrid(int x, int y)
{
	return Singleton::instance->map->getObj(x, y);
}

BuildSystem::BuildSystem() : buildLevel{0}, prevPos(-1, -1), building{nullptr}, keepObj{nullptr}
{
	resources.loadFromFile("./resources/MiniWorldSprites/Buildings/Wood/Resources.png");
	wall_1.loadFromFile("./resources/MiniWorldSprites/Buildings/Enemy/SpearWall.png");
	wall_2.loadFromFile("./resources/MiniWorldSprites/Buildings/Wood/Tower.png");
	wall_3.loadFromFile("./resources/MiniWorldSprites/Buildings/Wood/Tower2.png");
	keep.loadFromFile("./resources/MiniWorldSprites/Buildings/Wood/Keep.png");
	barracks.loadFromFile("./resources/MiniWorldSprites/Buildings/Wood/Barracks.png");
	archers.loadFromFile("./resources/MiniWorldSprites/Characters/Soldiers/Ranged/RedRanged/BowmanRed.png");

	wall_1_t.loadFromImage(wall_1, sf::IntRect(0, 16, 16, 16));
	wall_1_v.loadFromImage(wall_1, sf::IntRect(32, 16, 16, 16));
	wall_1_h.loadFromImage(wall_1, sf::IntRect(32, 0, 16, 16));

	wall_2_t.loadFromImage(wall_2, sf::IntRect(32, 48, 16, 16));
	wall_2_v.loadFromImage(wall_2, sf::IntRect(16, 32, 16, 16));
	wall_2_h.loadFromImage(wall_2, sf::IntRect(0, 32, 16, 16));

	wall_3_t.loadFromImage(wall_3, sf::IntRect(32, 48, 16, 16));
	wall_3_v.loadFromImage(wall_3, sf::IntRect(16, 32, 16, 16));
	wall_3_h.loadFromImage(wall_3, sf::IntRect(0, 32, 16, 16));

	keep_1.loadFromImage(keep, sf::IntRect(0, 32, 32, 32));
	keep_2.loadFromImage(keep, sf::IntRect(32, 32, 32, 32));
	keep_3.loadFromImage(keep, sf::IntRect(64, 32, 32, 32));

	cave.loadFromImage(resources, sf::IntRect(16, 48, 16, 16));
	lumber.loadFromImage(resources, sf::IntRect(0, 32, 16, 16));

	archerBarrack.loadFromImage(barracks, sf::IntRect(0, 48, 32, 16));
	archer.loadFromImage(archers, sf::IntRect(0, 0, 16, 16));
	//swordsmanBarrack.loadFromImage(barracks, sf::IntRect(16, 0, 16, 16));
}

void BuildSystem::Upgrade(sf::Vector2f pos)
{

}

bool BuildSystem::CheckBuild(sf::Vector2f pos, Buildings type, GameObject*& building)
{
	sf::Color n = sf::Color::Red;
	n.a = 155;
	sf::Color y = sf::Color::Green;
	y.a = 155;

	Building::WorkStation* station;
	GameObject* obj = getGameObjectInGrid(pos);
	sf::Vector2f center = Singleton::instance->map->GridCoordsToCenterCoords(pos.x, pos.y);
	//Добавить проверку и изменение пола
	switch (type)
	{
	case BuildSystem::Buildings::wall_1:
		building = static_cast<GameObject*>(new Building::Wall(center, &wall_1_t, 30));
		building->render->setColor(n);
		//building->render->setPosition(Singleton::instance->map->GridCoordsToCenterCoords(pos.x, pos.y));
		building->render->setOrigin(8, 8);
		if (obj == nullptr)
		{
			building->render->setColor(y);
			return true;
		}

		break;

	case BuildSystem::Buildings::wall_2:
		building = static_cast<GameObject*>(new Building::Wall(pos, &wall_2_t, 60));
		building->render->setColor(n);
		building->render->setPosition(Singleton::instance->map->GridCoordsToCenterCoords(pos.x, pos.y));
		building->render->setOrigin(8, 8);
		if (obj == nullptr)
		{
			building->render->setColor(y);
			return true;
		}
		break;

	case BuildSystem::Buildings::wall_3:
		building = static_cast<GameObject*>(new Building::Wall(pos, &wall_3_t, 120));
		building->render->setColor(n);
		building->render->setPosition(Singleton::instance->map->GridCoordsToCenterCoords(pos.x, pos.y));
		building->render->setOrigin(8, 8);
		if (obj == nullptr)
		{
			building->render->setColor(y);
			return true;
		}
		break;

	case BuildSystem::Buildings::keep_1:
		building = static_cast<GameObject*>(new Keep(pos, &keep_1, 100));
		building->render->setColor(n);
		building->render->setPosition(Singleton::instance->map->GridCoordsToCenterCoords(pos.x, pos.y));
		building->render->setOrigin(16, 16);
		if (keepObj != nullptr)
			return false;
		for (int y = -1; y < 2; y++)
		{
			for (int x = -1; x < 2; x++)
			{
				if (getGameObjectInGrid(sf::Vector2f(pos.x + x, pos.y + y)) != nullptr)
					return false;
			}
		}
		building->render->setColor(y);
		return true;

	case BuildSystem::Buildings::keep_2:
		building = static_cast<GameObject*>(new Keep(pos, &keep_2, 200));
		building->render->setColor(n);
		building->render->setPosition(Singleton::instance->map->GridCoordsToCenterCoords(pos.x, pos.y));
		building->render->setOrigin(16, 16);
		for (int y = -1; y < 2; y++)
		{
			for (int x = -1; x < 2; x++)
			{
				if (getGameObjectInGrid(sf::Vector2f(pos.x + x, pos.y + y)) != nullptr)
					return false;
			}
		}
		building->render->setColor(y);
		return true;

	case BuildSystem::Buildings::keep_3:
		building = static_cast<GameObject*>(new Keep(pos, &keep_3, 300));
		building->render->setColor(n);
		building->render->setPosition(Singleton::instance->map->GridCoordsToCenterCoords(pos.x, pos.y));
		building->render->setOrigin(16, 16);
		for (int y = -1; y < 2; y++)
		{
			for (int x = -1; x < 2; x++)
			{
				if (getGameObjectInGrid(sf::Vector2f(pos.x + x, pos.y + y)) != nullptr)
					return false;
			}
		}
		building->render->setColor(y);
		return true;

	case BuildSystem::Buildings::cave:
		station = new Building::WorkStation(pos, &cave, 30, Resources::resource::nothing, 2);
		building = static_cast<GameObject*>(station);
		building->render->setColor(n);
		building->render->setPosition(Singleton::instance->map->GridCoordsToCenterCoords(pos.x, pos.y));
		building->render->setOrigin(8, 8);
		if (Deposit* d = dynamic_cast<Deposit*>(obj))
		{
			if (d->type >= Resources::resource::iron && d->type <= Resources::resource::rock)
			{
				station->m_typeOfResource = d->type;
				building->render->setColor(y);
				return true;
			}
		}
		break;

	case BuildSystem::Buildings::lumber:
		station = new Building::WorkStation(Singleton::instance->map->GridCoordsToCenterCoords(pos.x, pos.y), &lumber, 30, Resources::resource::wood, 0);
		building = static_cast<GameObject*>(station);
		building->render->setColor(n);
		building->render->setOrigin(8, 8);
		if (obj == nullptr)
		{
			building->render->setColor(y);
			return true;
		}
		break;

	case BuildSystem::Buildings::archerBarrack:
		building = static_cast<GameObject*>(new Building::WorkStation(pos, &archerBarrack, 75, Resources::resource::archer, 1));
		building->render->setColor(n);
		building->render->setPosition(Singleton::instance->map->GridCoordsToCenterCoords(pos.x, pos.y));
		building->render->setOrigin(8, 8);
		if (obj == nullptr)
		{
			building->render->setColor(y);
			return true;
		}
		break;

	case BuildSystem::Buildings::archer:
		building = static_cast<GameObject*>(new Building::Archer(pos, &archer, 15));
		building->render->setColor(n);
		building->render->setPosition(Singleton::instance->map->GridCoordsToCenterCoords(pos.x, pos.y));
		building->render->setOrigin(8, 8);
		if (obj == nullptr)
		{
			building->render->setColor(y);
			return true;
		}
		if (dynamic_cast<Building::Wall*>(obj))
		{
			building->render->setPosition(building->render->getPosition() - sf::Vector2f(0, 4));
			building->render->setColor(y);
			return true;
		}

		break;

	default:
		break;
	}

	return false;
}

void BuildSystem::Build(sf::Vector2f pos, Buildings type, bool isBuild)
{
	Player* player = Singleton::instance->player;
	pos = Singleton::instance->map->CoordsToGridCoords(pos);

	if (prevPos != pos || isBuild)
	{
		if (building != nullptr)
			delete building;

		prevPos = pos;
		Resources p = resourceRequire[type];
		if (CheckBuild(pos, type, building))
		{
			if (building == nullptr)
				return;

			if (isBuild && p <= player->resource)
			{
				player->resource -= p;
				building->render->setColor(sf::Color::White);

				if (Building::WorkStation* station = dynamic_cast<Building::WorkStation*>(building))
				{
					station->isWorking = true;
					if (station->m_typeOfResource == Resources::resource::wood)
					{
						std::list<Collision::BaseCollider*> b = Engine::instance->m_collision->getCollisions(&station->gatherCollider);
						int treeCount = 0;
						for (auto i : b)
						{
							if (Collision::CircleCollider* c = dynamic_cast<Collision::CircleCollider*>(i))
							{
								if (!i->isTrigger)
								{
									if (Deposit* dep = dynamic_cast<Deposit*>(i->object))
									{
										if (dep->type == Resources::resource::wood)
											++treeCount;
									}
								}
							}
						}
						station->m_resourcesPer15sec = treeCount;
					}
				}

				if (type == Buildings::archer)
				{
					GameObject* obj = getGameObjectInGrid(pos);
					if (Building::Wall* wall = dynamic_cast<Building::Wall*>(obj))
					{
						wall->PlaceArcher(archer);
						delete building;
					}
				}

				if (type == Buildings::keep_1)
				{
					keepObj = building;
				}

				Singleton::instance->map->setObj(pos.x, pos.y, building);
			}
			else if(!(p <= player->resource))
				std::cout << "Need resources: wood:" << p.resources[Resources::resource::wood] << " iron:" << p.resources[Resources::resource::iron] <<
				" gold:" << p.resources[Resources::resource::gold] << " rock:" << p.resources[Resources::resource::rock] << " archer:" << p.resources[Resources::resource::archer] << std::endl;
		}
	
	}

	
}

void BuildSystem::PlaceCurrentBuilding(Buildings type)
{
	building->render->setColor(sf::Color::White);

	switch (type)
	{
	case BuildSystem::Buildings::wall_1:
		break;
	case BuildSystem::Buildings::wall_2:
		break;
	case BuildSystem::Buildings::wall_3:
		break;
	case BuildSystem::Buildings::cave:
		break;
	case BuildSystem::Buildings::lumber:
		break;
	case BuildSystem::Buildings::archerBarrack:
		break;
	case BuildSystem::Buildings::archer:
		break;
	case BuildSystem::Buildings::keep_1:
		break;
	case BuildSystem::Buildings::keep_2:
		break;
	case BuildSystem::Buildings::keep_3:
		break;
	case BuildSystem::Buildings::nothing:
		break;
	default:
		break;
	}

	building = nullptr;
}


void BuildSystem::Destroy(sf::Vector2f pos)
{
	GameObject* obj = getGameObjectInGrid(pos);
	if (dynamic_cast<Building::Wall*>(obj) || dynamic_cast<Building::WorkStation*>(obj) || dynamic_cast<Building::Archer*>(obj))
		delete obj;
}