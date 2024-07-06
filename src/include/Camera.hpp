#include <IUpdateable.hpp>

class Camera : public IUpdateable
{
public:
	bool m_down;
	bool m_up;
	bool m_right;
	bool m_left;
	float speed;

	Camera(float speed) : IUpdateable(), speed{speed}, m_down{false}, m_up{false}, m_left{false}, m_right{false}
	{

	}

	void Update() override;

};

#include <Engine.hpp>