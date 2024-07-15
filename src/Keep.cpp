#include <Keep.hpp>
#include <Engine.hpp>
Keep::Keep(const sf::Vector2f position, sf::Texture* texture, int health) : GameObject(position, texture), IHittable(health), collider{ this, position, 16 }, isDestroyed{false}
{
	render->setOrigin(16, 16);
}

bool Keep::Hit(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		isDestroyed = true;
		std::cout << "keep is destroyed\n";
		blackScreen = new sf::RectangleShape();
		blackScreen->setFillColor(sf::Color::Black);
		blackScreen->setSize(sf::Vector2f(Engine::instance->m_gameWidth * 32, Engine::instance->m_gameHeight * 32));
		blackScreen->setPosition(sf::Vector2f(0, 0));
		text = new sf::Text();
		sf::Font* f = new sf::Font();
		f->loadFromFile("./resources/tuffy.ttf");
		text->setFont(*f);
		text->setPosition(sf::Vector2f(0, Engine::instance->m_gameHeight / 2));
		text->setString("Game Over");
		text->setColor(sf::Color::White);
		Engine::instance->m_manualRender.push_back(blackScreen);
		Engine::instance->m_manualRender.push_back(text);
		return isDestroyed;
	}
	return isDestroyed;
}