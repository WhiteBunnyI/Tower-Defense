#pragma once

#include <Vector2.hpp>
#include <MapGenerator.hpp>
#include <Singleton.hpp>
#include <unordered_set>

namespace my
{
	namespace pathFinding
	{
		//Объявляем свои функцию, по которой будет считаться хэш и сравниваться указатели на Node

		struct Node
		{
			Vector2I pos;	//Координаты
			int g;			//Расстояние от начала до этой точки
			int h;			//Расстояние от конца до этой точки
			int f;			//Сумма g+h
			Node* parent;	//Родительский узел

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