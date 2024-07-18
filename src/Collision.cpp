#include <Collision.hpp>
#include <Engine.hpp>

//CircleCollider

Collision::CircleCollider::CircleCollider(GameObject* obj, sf::Vector2f center, float radius, bool isTrigger, bool isTempCollider) : BaseCollider(obj, center, isTrigger), radius{ radius }
{
	if (!isTempCollider)
		Collision::instance->UpdateCollider(this);
#ifdef DEBUG_COLLISION
	c = new sf::CircleShape();
	c->setRadius(radius);
	c->setOrigin(radius, radius);
	c->setFillColor(sf::Color::Transparent);
	c->setOutlineThickness(1);
	c->setOutlineColor(sf::Color::Red);
	c->setPosition(center);
	Engine::instance->m_manualRender.push_back(c);
#endif // DEBUG_COLLISION

}

Collision::CircleCollider::~CircleCollider()
{
	Collision::instance->RemoveCollider(this);
#ifdef DEBUG_COLLISION
	Engine::instance->m_manualRender.remove(c);
#endif // DEBUG_COLLISION

}

void Collision::CircleCollider::Update(sf::Vector2f center)
{
	this->center = center;
	Collision::instance->UpdateCollider(this);
#ifdef DEBUG_COLLISION
	c->setPosition(center);
#endif // DEBUG_COLLISION

}

//Collision

Collision::Collision(sf::Vector2i gridSize, sf::Vector2i mapSize) : gridSize{ gridSize }, mapSize{mapSize}
{
	if(mapSize.x % gridSize.x != 0 || mapSize.y % gridSize.y != 0)
		throw new std::runtime_error("Change grid size!");
	grid = new std::list<BaseCollider*>[gridSize.x * gridSize.y];

#ifdef DEBUG_COLLISION
	int sizeX = mapSize.x / gridSize.x;
	int sizeY = mapSize.y / gridSize.y;
	for (int y = 0; y < gridSize.y; ++y)
	{
		for (int x = 0; x < gridSize.x; ++x)
		{
			sf::RectangleShape* s = new sf::RectangleShape();
			s->setPosition(sf::Vector2f(x * sizeX + sizeX / 2.f, y * sizeY + sizeY / 2.f));
			s->setOrigin(sizeX / 2, sizeY / 2);
			s->setSize(sf::Vector2f(sizeX, sizeY));
			s->setOutlineThickness(1);
			s->setFillColor(sf::Color::Transparent);
			s->setOutlineColor(sf::Color::Green);
			Engine::instance->m_manualRender.push_back(s);
		}
	}
#endif // DEBUG
	instance = this;
}

std::list<Collision::BaseCollider*>& Collision::getList(sf::Vector2i gridPos)
{
	return grid[gridPos.x + gridPos.y * gridSize.x];
}

void Collision::UpdateCollider(BoxCollider* collider)
{
	int sizeX = mapSize.x / gridSize.x;
	int sizeY = mapSize.y / gridSize.y;
	sf::Vector2i gridPos(collider->center.x / sizeX, collider->center.y / sizeY);
	getList(gridPos).push_back(collider);
	for (int _y = -1; _y < 2; ++_y)
	{
		for (int _x = -1; _x < 2; ++_x)
		{
			if (_x == 0 && _y == 0)
				continue;
			sf::Vector2i otherGrid(gridPos.x + _x, gridPos.y + _y);
			if ((otherGrid.x >= 0 && otherGrid.x < gridSize.x) &&
				(otherGrid.y >= 0 && otherGrid.y < gridSize.y))
			{
				BoxCollider gridCollider(nullptr, sf::Vector2f(otherGrid.x * sizeX + sizeX / 2.f, otherGrid.y * sizeY + sizeY / 2.f), sf::Vector2f(sizeX / 2, sizeY / 2), true);
				if (CheckCollision(collider, &gridCollider))
				{
					getList(otherGrid).push_back(collider);
				}
			}
		}
	}
#ifdef DEBUG_COLLISION

	sf::RectangleShape* s = new sf::RectangleShape();
	s->setPosition(sf::Vector2f(gridPos.x * sizeX + sizeX / 2, gridPos.y * sizeY + sizeY / 2));
	s->setOrigin(sizeX / 2, sizeY / 2);
	s->setSize(sf::Vector2f(sizeX, sizeY));
	s->setOutlineThickness(1);
	s->setFillColor(sf::Color::Transparent);
	s->setOutlineColor(sf::Color::Green);
	Engine::instance->m_manualRender.push_back(s);

	s = new sf::RectangleShape();
	s->setPosition(collider->center);
	s->setOrigin(sf::Vector2f(collider->border.x, collider->border.y));
	s->setSize(sf::Vector2f(collider->border.x * 2, collider->border.y * 2));
	s->setOutlineThickness(1);
	s->setFillColor(sf::Color::Transparent);
	s->setOutlineColor(sf::Color::Magenta);
	Engine::instance->m_manualRender.push_back(s);

	sf::CircleShape* c = new sf::CircleShape();
	c->setRadius(4);
	c->setOrigin(4, 4);
	c->setFillColor(sf::Color::Transparent);
	c->setOutlineThickness(1);
	c->setOutlineColor(sf::Color::Red);
	c->setPosition(collider->center + collider->border);
	Engine::instance->m_manualRender.push_back(c);

	c = new sf::CircleShape();
	c->setRadius(4);
	c->setOrigin(4, 4);
	c->setFillColor(sf::Color::Transparent);
	c->setOutlineThickness(1);
	c->setOutlineColor(sf::Color::Blue);
	c->setPosition(collider->center - collider->border);
	Engine::instance->m_manualRender.push_back(c);

#endif // DEBUG

	
}

void Collision::UpdateCollider(CircleCollider* collider)
{
	int sizeX = mapSize.x / gridSize.x;
	int sizeY = mapSize.y / gridSize.y;
	sf::Vector2i gridPos(collider->center.x / sizeX, collider->center.y / sizeY);
	std::list<BaseCollider*>& l = getList(gridPos);
	l.remove(collider);
	l.push_back(collider);
	std::list<BaseCollider*>& l1 = getList(gridPos);

	for (int _y = -1; _y < 2; ++_y)
	{
		for (int _x = -1; _x < 2; ++_x)
		{
			if (_x == 0 && _y == 0)
				continue;
			sf::Vector2i otherGrid(gridPos.x + _x, gridPos.y + _y);
			if ((otherGrid.x >= 0 && otherGrid.x < gridSize.x) &&
				(otherGrid.y >= 0 && otherGrid.y < gridSize.y))
			{
				BoxCollider gridCollider(nullptr, sf::Vector2f(otherGrid.x * sizeX + sizeX / 2.f, otherGrid.y * sizeY + sizeY / 2.f), sf::Vector2f(sizeX / 2, sizeY / 2), true);
				std::list<BaseCollider*>& lst = getList(otherGrid);
				lst.remove(collider);
				if (CheckCollision(collider, &gridCollider))
				{
					lst.push_back(collider);
					continue;
				}
			}
		}
	}

}

void Collision::RemoveCollider(BaseCollider* collider)
{
	int sizeX = mapSize.x / gridSize.x;
	int sizeY = mapSize.y / gridSize.y;
	sf::Vector2i gridPos(collider->center.x / sizeX, collider->center.y / sizeY);
	std::list<BaseCollider*>& l = getList(gridPos);
	l.remove(collider);
	for (int _y = -1; _y < 2; ++_y)
	{
		for (int _x = -1; _x < 2; ++_x)
		{
			if (_x == 0 && _y == 0)
				continue;
			sf::Vector2i otherGrid(gridPos.x + _x, gridPos.y + _y);
			if ((otherGrid.x >= 0 && otherGrid.x < gridSize.x) &&
				(otherGrid.y >= 0 && otherGrid.y < gridSize.y))
			{
				std::list<BaseCollider*>& lst = getList(otherGrid);
				lst.remove(collider);
			}
		}
	}
}

void Collision::checkCollisions(BoxCollider* collider, std::list<BaseCollider*>& where_check, std::list<BaseCollider*>& saveTo)
{
	for (auto p : where_check)
	{
		if (p == collider)
			continue;
		if (CheckCollision(collider, p))
		{
			saveTo.push_back(p);
		}
	}
}

void Collision::checkCollisions(CircleCollider* collider, std::list<BaseCollider*>& where_check, std::list<BaseCollider*>& saveTo)
{
	for (auto p : where_check)
	{
		if (p == collider)
			continue;
		if (CheckCollision(collider, p))
		{
			saveTo.push_back(p);
		}
	}
}

std::list<Collision::BaseCollider*> Collision::getCollisions(BoxCollider* collider)
{
	std::list<BaseCollider*> result;

	int sizeX = mapSize.x / gridSize.x;
	int sizeY = mapSize.y / gridSize.y;

	sf::Vector2i gridPos(collider->center.x / sizeX, collider->center.y / sizeY);

	for (int _y = -1; _y < 2; ++_y)
	{
		for (int _x = -1; _x < 2; ++_x)
		{
			sf::Vector2i otherGrid(gridPos.x + _x, gridPos.y + _y);
			if (_x == 0 && _y == 0)
			{
				checkCollisions(collider, getList(otherGrid), result);
				continue;
			}

			if ((otherGrid.x >= 0 && otherGrid.x < gridSize.x) &&
				(otherGrid.y >= 0 && otherGrid.y < gridSize.y))
			{
				BoxCollider gridCollider(nullptr, sf::Vector2f(otherGrid.x * sizeX + sizeX / 2.f, otherGrid.y * sizeY + sizeY / 2.f), sf::Vector2f(sizeX / 2, sizeY / 2), true);
				if (CheckCollision(collider, &gridCollider))
				{
					checkCollisions(collider, getList(otherGrid), result);
				}
			}
		}
	}

	return result;
}

std::list<Collision::BaseCollider*> Collision::getCollisions(CircleCollider* collider)
{
	std::list<BaseCollider*> result;

	int sizeX = mapSize.x / gridSize.x;
	int sizeY = mapSize.y / gridSize.y;


	sf::Vector2i gridPos(collider->center.x / sizeX, collider->center.y / sizeY);

	for (int _y = -1; _y < 2; ++_y)
	{
		for (int _x = -1; _x < 2; ++_x)
		{
			sf::Vector2i otherGrid(gridPos.x + _x, gridPos.y + _y);
			if (_x == 0 && _y == 0)
			{
				checkCollisions(collider, getList(otherGrid), result);
				continue;
			}

			if ((otherGrid.x >= 0 && otherGrid.x < gridSize.x) &&
				(otherGrid.y >= 0 && otherGrid.y < gridSize.y))
			{
				BoxCollider gridCollider(nullptr, sf::Vector2f(otherGrid.x * sizeX + sizeX / 2.f, otherGrid.y * sizeY + sizeY / 2.f), sf::Vector2f(sizeX / 2, sizeY / 2), true);
				if (CheckCollision(collider, &gridCollider))
				{
					checkCollisions(collider, getList(otherGrid), result);
				}
			}
		}
	}

	return result;

}

bool Collision::CheckCollision(const CircleCollider* circle, const BoxCollider* box)
{
	sf::Vector2f b_leftTop = box->center - box->actualBorder;
	sf::Vector2f b_rightBottom = box->center + box->actualBorder;

	if ((b_leftTop.x <= circle->center.x && circle->center.x <= b_rightBottom.x) && (b_leftTop.y <= circle->center.y && circle->center.y <= b_rightBottom.y))
		return true;

	//Надо исправить: сделать, чтобы он учитывал поворот квадратного коллайдера, да и сам алгоритм не рабочий
	return ((std::abs(b_leftTop.x - circle->center.x) <= circle->radius) || (std::abs(b_rightBottom.x - circle->center.x) <= circle->radius)) &&
		((std::abs(b_leftTop.y - circle->center.y) <= circle->radius) || (std::abs(b_rightBottom.y - circle->center.y) <= circle->radius));
}

bool Collision::CheckCollision(const BoxCollider* box1, const BoxCollider* box2)
{
	sf::Vector2f b1_leftTop = box1->center - box1->actualBorder;
	sf::Vector2f b1_rightBottom = box1->center + box1->actualBorder;

	sf::Vector2f b2_leftTop = box2->center - box2->actualBorder;
	sf::Vector2f b2_rightBottom = box2->center + box2->actualBorder;

	return (((b1_leftTop.x <= b2_leftTop.x) && (b2_leftTop.x <= b1_rightBottom.x)) || ((b1_leftTop.x <= b2_rightBottom.x) && (b2_rightBottom.x <= b1_rightBottom.x))) &&
		(((b1_leftTop.y <= b2_leftTop.y) && (b2_leftTop.y <= b1_rightBottom.y)) || ((b1_leftTop.y <= b2_rightBottom.y) && (b2_rightBottom.y <= b1_rightBottom.y)));
}

bool Collision::CheckCollision(const CircleCollider* circle1, const CircleCollider* circle2)
{
	sf::Vector2f vec = circle1->center - circle2->center;
	if (std::sqrtf(vec.x * vec.x + vec.y * vec.y) <= circle1->radius + circle2->radius)
		return true;
	return false;
}

bool Collision::CheckCollision(const CircleCollider* circle, BaseCollider* collider)
{
	if (BoxCollider* box = dynamic_cast<BoxCollider*>(collider))
	{
		return CheckCollision(circle, box);
	}
	if (CircleCollider* circle2 = dynamic_cast<CircleCollider*>(collider))
	{
		return CheckCollision(circle, circle2);
	}
	return false;
}

bool Collision::CheckCollision(const BoxCollider* box, BaseCollider* collider)
{
	if (BoxCollider* box = dynamic_cast<BoxCollider*>(collider))
	{
		return CheckCollision(box, box);
	}
	if (CircleCollider* circle2 = dynamic_cast<CircleCollider*>(collider))
	{
		return CheckCollision(circle2, box);
	}
	return false;
}

bool Collision::CheckCollision(BaseCollider* collider1, BaseCollider* collider2)
{
	if (BoxCollider* box = dynamic_cast<BoxCollider*>(collider1))
	{
		return CheckCollision(box, collider2);
	}
	if (CircleCollider* circle = dynamic_cast<CircleCollider*>(collider1))
	{
		return CheckCollision(circle, collider2);
	}
	return false;
}