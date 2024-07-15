#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include <GameObject.hpp>

#define DEBUG_COLLISION



class Collision
{
	static inline Collision* instance{ nullptr };
public:
	struct BaseCollider;
	struct BoxCollider;
	struct CircleCollider;
private:
	sf::Vector2i gridSize;
	sf::Vector2i mapSize;

	std::list<BaseCollider*>* grid;

	std::list<BaseCollider*>& getList(sf::Vector2i gridPos);
	void checkCollisions(BoxCollider* collider, std::list<BaseCollider*>& where_check, std::list<BaseCollider*>& saveTo);
	void checkCollisions(CircleCollider* collider, std::list<BaseCollider*>& where_check, std::list<BaseCollider*>& saveTo);

public:
	Collision() = default;
	Collision(sf::Vector2i gridSize, sf::Vector2i mapSize);

	void UpdateCollider(BoxCollider* collider);
	void UpdateCollider(CircleCollider* collider);

	void RemoveCollider(BoxCollider* collider);
	void RemoveCollider(CircleCollider* collider);

	//¬озращ€ет список со всеми столкновени€ми
	const std::list<BaseCollider*> getCollisions(BoxCollider* collider);
	const std::list<BaseCollider*> getCollisions(CircleCollider* collider);

	bool CheckCollision(const CircleCollider* circle, const BoxCollider* box);
	bool CheckCollision(const BoxCollider* box1, const BoxCollider* box2);
	bool CheckCollision(const CircleCollider* circle1, const CircleCollider* circle2);
	bool CheckCollision(const CircleCollider* circle, BaseCollider* collider);
	bool CheckCollision(const BoxCollider* box, BaseCollider* collider);
	bool CheckCollision(BaseCollider* collider1, BaseCollider* collider2);

	struct BaseCollider
	{
		GameObject* object;
		sf::Vector2f center;
		bool isTrigger;
		BaseCollider() : object{ nullptr }, center{}, isTrigger{ false } {}
		virtual ~BaseCollider() = default;

		BaseCollider(GameObject* obj, sf::Vector2f center, bool isTrigger = false) : center{ center }, object{ obj }, isTrigger{ isTrigger }
		{
		
		}

	};

	struct BoxCollider : public BaseCollider
	{
		sf::Vector2f border;
		float angle;

		BoxCollider() = default;

		BoxCollider(GameObject* obj, sf::Vector2f center, sf::Vector2f border, bool isTempCollider = false) : BaseCollider(obj, center), border{ border }, angle{ 0 }, actualBorder{ border }
		{
			if(!isTempCollider)
				Collision::instance->UpdateCollider(this);
		}

		void Update(sf::Vector2f center, float angle)
		{
			this->center = center;
			this->angle = angle;

			float rad = angle * 3.14f / 180.f;
			actualBorder.x = border.x * std::cosf(rad) - border.y * std::sinf(rad);
			actualBorder.y = border.x * std::sinf(rad) + border.y * std::cosf(rad);
			Collision::instance->UpdateCollider(this);
		}
	private:
		sf::Vector2f actualBorder;
		friend class Collision;
	};

	struct CircleCollider : public BaseCollider
	{
		float radius;
#ifdef DEBUG_COLLISION
		sf::CircleShape* c;
#endif // DEBUG_COLLISION

		CircleCollider() = default;
		~CircleCollider() override;
		CircleCollider(GameObject* obj, sf::Vector2f center, float radius, bool isTrigger = false, bool isTempCollider = false);
		void Update(sf::Vector2f center);
	};
};

