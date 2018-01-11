#ifndef ZOMBIEGAME_OBJECTS
#define ZOMBIEGAME_OBJECTS
#include <sge_reactive.hpp>
#include <sge_being.hpp>
#include "Dynamics/b2Body.h"

class Physical : public SGE::Being
{
	//For testing
public:
	using Being::Being;
	b2Body* body;
	
	glm::vec2 getPosition() const noexcept override;
	void setPosition(float,float) override;
	float getX() const noexcept override;
	float getY() const noexcept override;

	virtual void setBody(b2Body* b2Body);
	virtual void addFixture(const b2FixtureDef& humanFixture);
	virtual void addFixture(const b2Shape& humanFixture);
};

class Player : public Physical
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

class Human : public Physical
{
	glm::vec2 velocity = { 200.f,0.f };
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

class Image : public SGE::Object
{
public:
	using Object::Object;
};

#endif
