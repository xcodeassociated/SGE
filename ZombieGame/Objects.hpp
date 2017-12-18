#ifndef ZOMBIEGAME_OBJECTS
#define ZOMBIEGAME_OBJECTS
#include <sge_reactive.hpp>
#include <sge_being.hpp>

class Player : public SGE::Reactive
{
public:
	Player();

	Player(const float x, const float y);
};

class Portal : public SGE::Reactive
{
public:
	using SGE::Reactive::Reactive;

	Portal(float x, float y);
};

class Human : public SGE::Being
{
	glm::vec2 velocity = { 100.f,0.f };
	unsigned int counter = 1;
	unsigned int maxCount = 0;

public:
	Human(const float x, const float y);

	Human(const float x, const float y, const unsigned int max);

	void setMaxCount(const unsigned int max);

	unsigned int getCounter();

	glm::vec2 getVelocity() const;

	void setVelocity(const glm::vec2 vel);
};

#endif
