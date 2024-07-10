#include <Player.hpp>
#include <Singleton.hpp>

Player::Player() : GameObject(), m_camera{ 240, 2 }
{
	sf::Vector2f pos = Singleton::instance->map->getPlayerCoordsSpawn();
	m_camera.SetPosition(pos);
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("./resources/player.png");
	render->setTexture(*texture, true);
	render->setPosition(pos);
}

void Player::Start()
{

}

void Player::Update()
{
	render->setPosition(Engine::instance->m_view->getCenter());
}
