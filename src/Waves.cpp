#include <Waves.hpp>
#include <Engine.hpp>
#include <Enemy.hpp>

Waves::Waves() : IUpdateable(), currentCount{15}, timer{15}
{
	enemyTexture = new sf::Texture();
	sf::Image enemyImage;
	enemyImage.loadFromFile("./resources/MiniWorldSprites/Characters/Monsters/Undead/Skeleton-Soldier.png");
	enemyTexture->loadFromImage(enemyImage, sf::IntRect(16, 0, 16, 16));
}

void Waves::Update()
{
	timer -= Engine::instance->deltaTime;
	if (timer <= 0)
	{
		timer = 60;
		int offset = std::sqrtf(currentCount);
		for (int i = 0; i < currentCount; i++)
		{
			sf::Vector2f pos(offset / 2 + offset % (i+1), offset / 2 + offset / (i+1));
			Enemy* enemy = new Enemy(pos, enemyTexture, 50, 5, 3, 1.5f);
		}

		currentCount *= multiplyEnemys;
	}
}