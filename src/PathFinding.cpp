#include <PathFinding.hpp>

my::pathFinding::Node::Node(int x, int y) : Node()
{
	pos = Vector2I(x, y);
}


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
	return std::sqrtf(x * x + y * y) * 10;
}

void my::pathFinding::PathFinding::Clear()
{
	for (auto ptr : checked)
	{
		delete ptr;
	}
	checked.clear();

	for (auto ptr : awaits)
	{
		delete ptr;
	}
	awaits.clear();
}

my::pathFinding::PathFinding::~PathFinding()
{
	Clear();
}

my::pathFinding::Node* my::pathFinding::PathFinding::CalculatePath(Vector2I a, Vector2I b, float mul)
{
	Clear();
	MapGenerator* map = Singleton::instance->map;

	Node* current = new Node();
	current->pos = a;
	current->g = 0;
	current->h = distance(a, b);
	current->parent = nullptr;
	current->calculate();

	while (current->pos != b)
	{
		checked.insert(current);
		for (int y = -1; y < 2; ++y)
		{
			for (int x = -1; x < 2; ++x)
			{
				//������� ������� �����
				if (x == 0 && y == 0)
					continue;

				int _x = current->pos.x + x;
				int _y = current->pos.y + y;

				//��������� �������
				if (_x < 0 || _x >= map->getSize().x)
					continue;
				if (_y < 0 || _y >= map->getSize().y)
					continue;

				
				Node n(_x, _y);
				//������� ������, ������� �� ��� ��������� ��� ������� ������� ��������
				if (checked.find(&n) != checked.end() || awaits.find(&n) != awaits.end())
					continue;
					

				//������� �������, �� ������� ������ ������
				Tile* tile = map->getTile(_x, _y);

				if (tile->speed == 0)
					continue;
				bool isEmpty = !(map->IsBuilding(_x, _y));
				Node* node = new Node();
				node->pos = Vector2I(_x, _y);
				node->g = current->g + distance(current->pos, node->pos) * (2.f - tile->speed * isEmpty) * mul;
				node->h = distance(node->pos, b);
				node->parent = current;
				node->calculate();

				awaits.insert(node);
			}
		}


		//����������� ������ ��� ��������
		if (awaits.size() == 0)
			break;

		/*current = *(awaits.begin());

		for (auto p = awaits.begin(); p != awaits.end(); ++p)
		{
			if (current->f > (*p)->f)
				current = (*p);
		}*/

		auto p = awaits.begin();
		auto end = *(--awaits.end());
		current = *(p);
		for (int i = 0; i < Singleton::instance->map->getSize().x * Singleton::instance->map->getSize().y / 10; ++i)
		{
			if (current->f > (*p)->f)
				current = (*p);

			if (*p == end)
				break;
			++p;
		}

		//������� �� ���� ������, ��������� ��������
		awaits.erase(current);
	}

	//����� ���� �� ����� b
	if (current->pos == b)
		return current;

	Clear();
	//�� ����� :(
	return nullptr;
}