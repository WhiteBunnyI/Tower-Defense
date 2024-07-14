#include <Enemy.hpp>
#include <ThreadPool.hpp>
#include <Singleton.hpp>

using Node = my::pathFinding::Node;
using PathFinding = my::pathFinding::PathFinding;

Enemy::Enemy(const sf::Vector2f position, sf::Texture* texture, int health) : isDead{ false }
{
	m_health = health;
}

void Enemy::Damage(int damage)
{
	if (isDead)
		return;

	m_health -= damage;
	if (m_health <= 0)
	{
		isDead = true;
	}
}

void Enemy::Update()
{
	if (isDead)
		return;

	auto func = [this](my::ThreadHolderWithData<Node*, Enemy*> instance)
		{
			Enemy* enemy = instance.get<0>();

			MapGenerator* map = Singleton::instance->map;
			Player* player = Singleton::instance->player;
			sf::Vector2f currentPosInGrid = map->CoordsToGridCoords(enemy->render->getPosition());
			sf::Vector2f playerPosInGrid = map->CoordsToGridCoords(player->render->getPosition());

			enemy->finder->CalculatePath(currentPosInGrid, playerPosInGrid);
		};

}

void Enemy::LateUpdate()
{
	if (isDead)
		return;

	if()
}