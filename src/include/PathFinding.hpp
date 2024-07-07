#pragma once

#include <Vector2.hpp>
#include <unordered_set>
#include <list>

namespace my
{
	class PathFinding
	{
		class Node;
		std::unordered_set<Node*> checked;
		std::unordered_set<Node*> awaits;
	public:
		PathFinding() = default;

		int distance(Vector2I a, Vector2I b)
		{
			int x = b.x - a.x;
			int y = b.y - a.y;
			return std::sqrtf(x * x + y * y);
		}

		Node* CalculatePath(Vector2I a, Vector2I b)
		{
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
						
					}
				}
			}
		}

		void Clear()
		{

		}

		struct Node
		{
			Vector2I pos;	//Координаты
			int g;			//Расстояние от начала до этой точки
			int h;			//Расстояние от конца до этой точки
			int f;			//Сумма g+h
			Node* parent;	//Родительский узел

			void calculate()
			{
				f = g + h;
			}

			bool operator >(Node& other)
			{
				return (f > other.f);
			}
			bool operator==(Node& other)
			{
				return ((pos.x == other.pos.x) && (pos.y == other.pos.y));
			}
		};
	};
}