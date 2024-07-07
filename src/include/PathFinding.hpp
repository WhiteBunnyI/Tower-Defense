#pragma once

#include <Vector2.hpp>

class PathFinding
{
	class Node;

public:
	PathFinding() = default;

	Node* CalculatePath(Vector2I a, Vector2I b);

	void Clear();

	class Node
	{
		Vector2I pos;
		int g;			//Расстояние от начала до этой точки
		int h;			//Расстояние от конца до этой точки
		int f;			//Сумма g+h
		Node* parent;	//Родительский узел

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