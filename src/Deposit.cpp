#include <Deposit.hpp>

Deposit::Deposit(const sf::Vector2f position, sf::Texture* texture, int health, int resourceCount, Resources::resource typeResource) : 
	GameObject(position, texture),
	IMineable(resourceCount, health, typeResource),
	collider{ this, position, 5 }
{

}

int Deposit::Mine(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
		return m_resourceCount;
	int countByDamage = m_maxResource / m_maxHealth * damage;
	m_resourceCount -= countByDamage;
	return countByDamage;
}