#include <Player.hpp>
#include <Singleton.hpp>

Player::Player(float speed, float sprintMultiple) : GameObject(), speed{ speed }, sprintMultiple{ sprintMultiple }
{
	sf::Vector2f pos = Singleton::instance->map->getPlayerCoordsSpawn();
	pos = sf::Vector2f(5, 5);
	m_camera.SetPosition(pos);
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("./resources/player.png");
	render->setOrigin(Singleton::instance->map->m_texturesSize / 2.f, Singleton::instance->map->m_texturesSize / 2.f);
	render->setTexture(*texture, true);
	render->setPosition(pos);
}

void Player::Start()
{

}

void Player::Update()
{
	auto map = Singleton::instance->map;

	sf::Vector2f vec(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		vec.y += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		vec.y -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		vec.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		vec.x += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		vec *= sprintMultiple;

	vec *= Engine::instance->deltaTime;

	auto prediction = render->getPosition();
	sf::Vector2f currentGridCoords = map->CoordsToGridCoords(prediction);
	prediction.x += vec.x;
	prediction.y += vec.y;

	//currentGridCoords.x = std::rint(currentGridCoords.x);
	//currentGridCoords.y = std::rint(currentGridCoords.y);

	sf::Vector2f targetGridCoordsX(currentGridCoords);
	sf::Vector2f targetGridCoordsY(currentGridCoords);
	if (vec.x > 0)
		targetGridCoordsX.x += 0.5f;
	else if (vec.x < 0)
		targetGridCoordsX.x -= 0.5f;
	if (vec.y > 0)
		targetGridCoordsY.y += 0.5f;
	else if (vec.y < 0)
		targetGridCoordsY.y -= 0.5f;

	float tileSpeed = map->getTile(currentGridCoords.x, currentGridCoords.y)->speed;
	
	Tile* targetTileX = map->getTile(sf::Vector2i(targetGridCoordsX.x, targetGridCoordsX.y));
	Tile* targetTileY = map->getTile(sf::Vector2i(targetGridCoordsY.x, targetGridCoordsY.y));

	std::cout << "Pos: " << (render->getPosition()).x << ", " << (render->getPosition()).y << " | roundPos: " << currentGridCoords.x << ", " << currentGridCoords.y << " | gridX: " << targetGridCoordsX.x << ", " << targetGridCoordsX.y << " | gridY: " << targetGridCoordsY.x << ", " << targetGridCoordsY.y << std::endl;

	//nullptr == ����� �� �������, speed = 0 == ���� ��� ������
	if (targetTileX == nullptr || targetTileX->speed == 0)
	{
		vec.x = 0;
	}

	if (targetTileY == nullptr || targetTileY->speed == 0)
	{
		vec.y = 0;
	}
	m_camera.Move(vec);
	render->move(vec);
}
