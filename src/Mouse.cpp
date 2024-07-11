#include <Mouse.hpp>

Mouse::Mouse() : IUpdateable(), input{ Engine::instance->m_input }
{
	
}

void Mouse::Update()
{
	if (input->isPressed(sf::Mouse::Left))
	{

	}
}

//using Node = my::pathFinding::Node;
//
//void DrawLine(Vector2I a, Vector2I b)
//{
//	sf::RectangleShape* line = new sf::RectangleShape();
//	MapGenerator* map = Singleton::instance->map;
//	float dx = (b.x - a.x) * map->m_texturesSize;
//	float dy = (b.y - a.y) * map->m_texturesSize;
//	float dist = std::sqrtf(dx * dx + dy * dy);
//	line->setSize(sf::Vector2f(dist, map->m_texturesSize / 4));
//	line->setFillColor(sf::Color::Black);
//	line->setOrigin(0, map->m_texturesSize / 8);
//	line->setPosition((map->GridCoordsToCenterCoords(a.x, a.y)));
//	float angle = std::atan2(dy, dx) * (180.f/3.14f);
//	line->rotate(angle);
//	Engine::instance->m_manualRender.push_back(line);
//}
//
//void DrawPath(Node* n)
//{
//	while (n != nullptr && n->parent != nullptr)
//	{
//		DrawLine(n->pos, n->parent->pos);
//		n = n->parent;
//	}
//}
//
//Mouse::Mouse() : IUpdateable(), window{ Engine::instance->m_window }, a{ 0,0 }, b{ 0,0 }, isCalculatePath{ false }, input{Engine::instance->m_input}
//{
//
//}
//
//void Mouse::Update()
//{
//	if (window->hasFocus() && input->isPressed(sf::Mouse::Left))
//	{
//		auto window = Engine::instance->m_window;
//		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
//		int size = Singleton::instance->map->m_texturesSize;
//		a = Vector2I(mousePos.x / size, mousePos.y / size);
//#ifdef DEBUG_PATHFINDING
//		std::cout << "Coords: " << a.x << ", " << a.y << std::endl;
//		sf::CircleShape* shape = new sf::CircleShape(5.f);
//		shape->setPosition(a.x * size + size / 2, a.y * size + size / 2);
//		shape->setOrigin(5, 5);
//		shape->setFillColor(sf::Color::Blue);
//		Engine::instance->m_manualRender.push_back(shape);
//#endif // DEBUG_PATHFINDING
//		
//	}
//
//	if (window->hasFocus() && input->isPressed(sf::Mouse::Right))
//	{
//		auto window = Engine::instance->m_window;
//		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
//		int size = Singleton::instance->map->m_texturesSize;
//		b = Vector2I(mousePos.x / size, mousePos.y / size);
//#ifdef DEBUG_PATHFINDING
//		std::cout << "Coords: " << b.x << ", " << b.y << std::endl;
//		sf::CircleShape* shape = new sf::CircleShape(5.f);
//		shape->setPosition(b.x * size + size / 2, b.y * size + size / 2);
//		shape->setOrigin(5, 5);
//		shape->setFillColor(sf::Color::Red);
//		Engine::instance->m_manualRender.push_back(shape);
//#endif // DEBUG_PATHFINDING
//	}
//
//	if (window->hasFocus() && input->isPressed(sf::Keyboard::Space))
//	{
//		isCalculatePath = true;
//		std::cout << "Просчитываем путь..." << std::endl;
//		std::function<Node*(my::ThreadHolderWithData<Node*, my::pathFinding::PathFinding*, Vector2I, Vector2I>&)> func = [](my::ThreadHolderWithData<Node*, my::pathFinding::PathFinding*, Vector2I, Vector2I>& holder)
//			{
//				my::pathFinding::PathFinding* f = holder.get<0>();
//				Vector2I a = holder.get<1>();
//				Vector2I b = holder.get<2>();
//				auto result = f->CalculatePath(a, b);
//				return result;
//			};
//
//		result = Engine::instance->threadPool.enqueueD<Node*, my::pathFinding::PathFinding*, Vector2I, Vector2I>(func, &finder, a, b);
//	}
//
//}
//void Mouse::LateUpdate()
//{
//	if (isCalculatePath)
//	{
//		isCalculatePath = false;
//#ifdef DEBUG_PATHFINDING
//		Node* p = result.get();
//
//		std::cout << "Путь был успешно просчитан!" << std::endl;
//		if (p != nullptr)
//		{
//			std::cout << "Рисуем путь..." << std::endl;
//			DrawPath(p);
//		}
//#endif // DEBUG_PATHFINDING
//
//	}
//}

