#include <Mouse.hpp>
#include <Singleton.hpp>
Mouse::Mouse() : IUpdateable(), timer{ true }, window{Engine::instance->m_window} {}

void func(Coroutine<Mouse*>& instance)
{
	auto p = instance.get<0>();
	p->timer = true;
}

void Mouse::Update()
{
	if (timer && sf::Mouse::isButtonPressed(sf::Mouse::Left) && window->hasFocus())
	{
		timer = false;
		auto window = Engine::instance->m_window;
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		std::cout << "Coords: " << mousePos.x / Singleton::instance->map->m_texturesSize << ", " << mousePos.y / Singleton::instance->map->m_texturesSize << std::endl;
		sf::CircleShape* shape = new sf::CircleShape(5.f);
		shape->setPosition(mousePos);
		shape->setOrigin(5, 5);
		shape->setFillColor(sf::Color::Blue);
		Engine::instance->m_manualRender.push_back(shape);

		Coroutine<Mouse*>* cor = new Coroutine<Mouse*>(func, 0.15f, this);
		cor->Start();
	}

}

