#include <IUpdateable.hpp>

class Camera : public IUpdateable
{
public:
	float speed;
	float sprintMul;

	Camera(float speed, float sprintMultiple) : IUpdateable(), speed{ speed }, sprintMul{ sprintMultiple }
	{

	}

	void Update() override;

};

#include <Engine.hpp>