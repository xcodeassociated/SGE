#ifndef ZOMBIEGAME_LOGICS
#define ZOMBIEGAME_LOGICS

#include <sge_logic.hpp>
#include <sge_logic_collide.hpp>
#include <vector>
#include <random>
#include "Objects.hpp"
#include "sge_key.hpp"
#include "sge_camera2d.hpp"

class SimpleMove : public SGE::Logic
{
	float speed = 0;
	const SGE::Key up;
	const SGE::Key down;
	const SGE::Key left;
	const SGE::Key right;
	SGE::Reactive* object = nullptr;
public:
	SimpleMove(SGE::Reactive* object, const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right);
	void performLogic() override;
};

class BiCollider : public SGE::Logic
{
	SGE::Object* a = nullptr;
	SGE::Object* b = nullptr;

public:
	BiCollider(SGE::Object* a, SGE::Object* b);

	virtual void performLogic() override;
};

class PortalLogic : public SGE::Logics::Collide
{
	SGE::Object* portal = nullptr;
	SGE::Object* player = nullptr;

public:
	PortalLogic(SGE::Object* portal, SGE::Object* player);

	virtual void performLogic() override;
};

class HumanRandomMovement : public SGE::Logic
{
	std::vector<Human*>* humans = nullptr;
	std::default_random_engine engine;
	std::uniform_real_distribution<float> angle;
	b2Vec2 velocity;

public:
	explicit HumanRandomMovement(std::vector<Human*>* humans);

	virtual void performLogic() override;
};

class SnapCamera : public SGE::Logic
{
	const float speed = 0;
	const SGE::Key up, down, left, right, snapKey;
	bool snapped = true;
	SGE::Object* snapTo = nullptr;
	SGE::Camera2d* cam = nullptr;

public:
	SnapCamera(const float specamed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right, const SGE::Key snapKey, SGE::Object* snapTo, SGE::Camera2d* cam);

	~SnapCamera() = default;

	void performLogic() override;
};

class Timer : public SGE::Logic
{
	float time = .0f;
	SGE::Action* action = nullptr;
public:
	Timer(float time, SGE::Action* action);
	void performLogic() override;
};

#endif
