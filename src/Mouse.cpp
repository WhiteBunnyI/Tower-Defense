#include <Mouse.hpp>

Mouse::Mouse() : IUpdateable(), timer{ true } {}

void Mouse::Update()
{
	if (timer && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		timer = false;
		std::cout << "Create a mouse pointer" << std::endl;
		auto window = Engine::instance->m_window;
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

		sf::CircleShape* shape = new sf::CircleShape(1.f);
		shape->setPosition(mousePos);
		shape->setFillColor(sf::Color::Blue);
		Engine::instance->m_manualRender.push_back(shape);

		auto p{ [](Coroutine<Mouse*>& instance)
			{
				auto p = instance.get<0>();
				p->timer = true;
			}
		};
		Coroutine<Mouse*>* cor = new Coroutine<Mouse*>(p, 0.5f, this);
		cor->Start();
	}

}