#include <IMovable.hpp>

class Camera : public IMovable
{
public:
	void Move(Vector2 newPos) override;
};

#include <Engine.hpp>