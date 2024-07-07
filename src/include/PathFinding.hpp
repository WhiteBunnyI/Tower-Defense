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
		int g;			//���������� �� ������ �� ���� �����
		int h;			//���������� �� ����� �� ���� �����
		int f;			//����� g+h
		Node* parent;	//������������ ����

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