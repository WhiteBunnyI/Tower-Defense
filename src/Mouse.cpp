#include <Mouse.hpp>
#include <Singleton.hpp>

using Node = my::pathFinding::Node;

void func(Coroutine<Mouse*>& instance)
{
	auto p = instance.get<0>();
	p->timer = true;
}

void DrawLine(Vector2I a, Vector2I b)
{
	sf::RectangleShape* line = new sf::RectangleShape();
	MapGenerator* map = Singleton::instance->map;
	float dx = (b.x - a.x) * map->m_texturesSize;
	float dy = (b.y - a.y) * map->m_texturesSize;
	float dist = std::sqrtf(dx * dx + dy * dy);
	line->setSize(sf::Vector2f(dist, map->m_texturesSize / 4));
	line->setFillColor(sf::Color::Black);
	line->setOrigin(0, map->m_texturesSize / 8);
	line->setPosition((map->translateCoordsToGridCoords(a.x, a.y)));
	float angle = std::atan2(dy, dx) * (180.f/3.14f);
	line->rotate(angle);
	Engine::instance->m_manualRender.push_back(line);
}

void DrawPath(Node* n)
{
	while (n != nullptr && n->parent != nullptr)
	{
		DrawLine(n->pos, n->parent->pos);
		n = n->parent;
	}
}

Mouse::Mouse() : IUpdateable(), timer{ true }, window{ Engine::instance->m_window }
{
	cor = new Coroutine<Mouse*>(func, .15f, this, false);
}

void Mouse::Update()
{
	if (timer && window->hasFocus() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		timer = false;
		auto window = Engine::instance->m_window;
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		int size = Singleton::instance->map->m_texturesSize;
		a = Vector2I(mousePos.x / size, mousePos.y / size);
		std::cout << "Coords: " << a.x << ", " << a.y << std::endl;
		sf::CircleShape* shape = new sf::CircleShape(5.f);
		shape->setPosition(a.x * size + size / 2, a.y * size + size / 2);
		shape->setOrigin(5, 5);
		shape->setFillColor(sf::Color::Blue);
		Engine::instance->m_manualRender.push_back(shape);
		
		cor->Start();
	}

	if (timer && window->hasFocus() && sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		timer = false;
		auto window = Engine::instance->m_window;
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		int size = Singleton::instance->map->m_texturesSize;
		b = Vector2I(mousePos.x / size, mousePos.y / size);
		std::cout << "Coords: " << b.x << ", " << b.y << std::endl;
		sf::CircleShape* shape = new sf::CircleShape(5.f);
		shape->setPosition(b.x * size + size / 2, b.y * size + size / 2);
		shape->setOrigin(5, 5);
		shape->setFillColor(sf::Color::Red);
		Engine::instance->m_manualRender.push_back(shape);

		cor->Start();
	}

	if (timer && window->hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		timer = false;
		std::cout << "Просчитываем путь..." << std::endl;
		Node* p = finder.CalculatePath(a, b);
		std::cout << "Путь был успешно просчитан!" << std::endl;

		if(p != nullptr)
		{
			std::cout << "Путь оказался найден!" << std::endl;
			DrawPath(p);
		}
		cor->Start();
	}

}

