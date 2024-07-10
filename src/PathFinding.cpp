#include <PathFinding.hpp>

std::size_t my::pathFinding::NodePtrHash::operator()(const my::pathFinding::Node* f) const
{
	return (f->pos.x + static_cast<size_t>(f->pos.y) * Singleton::instance->map->getSize().x);
}

bool my::pathFinding::NodePtrEqual::operator()(const my::pathFinding::Node* lhs, const my::pathFinding::Node* rhs) const {
	return *lhs == *rhs;
}

void my::pathFinding::Node::calculate()
{
	f = g + h;
}

bool my::pathFinding::Node::operator >(const Node& other) const
{
	return (f > other.f);
}
bool my::pathFinding::Node::operator==(const Node& other) const
{
	return ((pos.x == other.pos.x) && (pos.y == other.pos.y));
}


float my::pathFinding::PathFinding::distance(Vector2I a, Vector2I b)
{
	float x = b.x - a.x;
	float y = b.y - a.y;
	return std::sqrtf(x * x + y * y);
}

void my::pathFinding::PathFinding::Clear()
{
	for (auto iter = checked.begin(); iter != checked.end(); ++iter)
	{
		delete (*iter);
	}
	checked.clear();

	for (auto iter = awaits.begin(); iter != awaits.end(); ++iter)
	{
		delete (*iter);
	}
	awaits.clear();
}

my::pathFinding::PathFinding::~PathFinding()
{
	Clear();
}

my::pathFinding::Node* my::pathFinding::PathFinding::CalculatePath(Vector2I a, Vector2I b)
{
	Clear();
	MapGenerator* map = Singleton::instance->map;

	Node* current = new Node();
	current->pos = a;
	current->g = 0;
	current->h = distance(a, b);
	current->parent = nullptr;
	current->calculate();
	checked.insert(current);

	while (current->pos != b)
	{
		for (int y = -1; y < 2; ++y)
		{
			for (int x = -1; x < 2; ++x)
			{
				//Игнорим текущую точку
				if (x == 0 && y == 0)
					continue;

				int _x = current->pos.x + x;
				int _y = current->pos.y + y;

				//Проверяем границы
				if (_x < 0 || _x >= map->getSize().x)
					continue;
				if (_y < 0 || _y >= map->getSize().y)
					continue;

				Node* node = new Node();
				node->pos = Vector2I(_x, _y);

				//Игнорим клетки, которые мы уже проверили
				if (checked.find(node) != checked.end())
					continue;

#pragma warning (disable: 4533)
				//Игнорим объекты, по которым нельзя ходить
				Tile::Type tile = map->getTile(_x, _y);
#pragma warning (default: 4533)
				float speed = Tile::MoveSpeed(tile);
				if (speed == 0)
					continue;

				node->g = current->g + distance(current->pos, node->pos) * 10.f * (2.f - speed);
				node->h = distance(node->pos, b);
				node->parent = current;
				node->calculate();

				awaits.insert(node);
			}
		}

		checked.insert(current);

		//Закончились клетки для проверки
		if (awaits.size() == 0)
			break;

		current = *(awaits.begin());

		for (auto p = awaits.begin(); p != awaits.end(); ++p)
		{
			if (current->f > (*p)->f)
				current = (*p);
		}

		//Убираем из сета клеток, ожидающих проверку
		awaits.erase(current);
	}

	//Нашли путь до точки b
	if (current->pos == b)
		return current;

	//Не нашли :(
	return nullptr;
}