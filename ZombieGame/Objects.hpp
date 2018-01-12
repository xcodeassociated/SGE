#ifndef ZOMBIEGAME_OBJECTS
#define ZOMBIEGAME_OBJECTS
#include <sge_reactive.hpp>
#include "sge_shape_circle.hpp"

inline SGE::Shape* getCircle()
{
	static SGE::Circle c(32, false);
	return &c;
}

class Player : public SGE::Reactive
{
public:
	using Reactive::Reactive;
};

class Portal : public SGE::Reactive
{
public:
	using SGE::Reactive::Reactive;

	Portal(float x, float y);
};

class Human : public SGE::Reactive
{
	b2Vec2 velocity = { 200.f,0.f };
	unsigned int counter = 1;
	unsigned int maxCount = 0;

public:
	Human(const float x, const float y);

	Human(const float x, const float y, const unsigned int max);

	void setMaxCount(const unsigned int max);

	unsigned int getCounter();

	b2Vec2 getVelocity() const;

	void setVelocity(const b2Vec2 vel);
};

class Image : public SGE::Object
{
public:
	using Object::Object;
};

#endif
