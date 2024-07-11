#pragma once

#include <Vector2.hpp>
#include <MapGenerator.hpp>
#include <Singleton.hpp>
#include <unordered_set>

namespace my
{
	namespace pathFinding
	{
		//��������� ���� �������, �� ������� ����� ��������� ��� � ������������ ��������� �� Node

		struct Node
		{
			Vector2I pos;	//����������
			int g;			//���������� �� ������ �� ���� �����
			int h;			//���������� �� ����� �� ���� �����
			int f;			//����� g+h
			Node* parent;	//������������ ����

			Node() = default;
			Node(int x, int y);

			void calculate();

			bool operator >(const Node& other) const;
			bool operator==(const Node& other) const;
		};

		struct NodePtrHash
		{
			size_t operator()(const my::pathFinding::Node* f) const;
		};

		struct NodePtrEqual
		{
			bool operator()(const my::pathFinding::Node* lhs, const my::pathFinding::Node* rhs) const;
		};

		class PathFinding
		{
			std::unordered_set<Node*, NodePtrHash, NodePtrEqual> checked;
			std::unordered_set<Node*, NodePtrHash, NodePtrEqual> awaits;

			float distance(Vector2I a, Vector2I b);

		public:
			PathFinding() = default;

			void Clear();

			~PathFinding();

			Node* CalculatePath(Vector2I a, Vector2I b);


		};
	}
}