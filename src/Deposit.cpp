#include <Deposit.hpp>
#include <Singleton.hpp>

Deposit::Deposit(const sf::Vector2f position, sf::Texture* texture, int health, int resourceCount, Resources::resource typeResource) :
	GameObject(position, texture),
	IMineable(resourceCount, health, typeResource),
	collider{ this, position, 5, false },
	isDestroyed{ false } {}

Deposit::~Deposit()
{
	MapGenerator* map = Singleton::instance->map;
	sf::Vector2f pos = map->CoordsToGridCoords(render->getPosition());
	map->getObj(pos.x, pos.y) = nullptr;
}

int Deposit::Mine(int damage)
{
	int dH = m_maxHealth / m_maxResource;
	int dR = m_maxResource / dH;
	int countByDamage = 0;
	if ((m_health - damage) < (m_health / dH) * dH)
		countByDamage = 1;
	m_health -= damage;
	if (m_health <= 0)
	{
		isDestroyed = true;
		return m_resourceCount;
	}
	m_resourceCount -= countByDamage;
	return countByDamage;
}

bool Deposit::IsDestroyed()
{
	return isDestroyed;
}
