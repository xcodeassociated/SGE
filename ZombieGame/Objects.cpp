#include "Objects.hpp"
#include <sge_shape_rectangle.hpp>

Portal::Portal(float x, float y): SGE::Reactive(x, y, true, new SGE::Rectangle(64, 64))
{
}

Human::Human(const float x, const float y): Reactive(x, y, true, getCircle())
{
}

Human::Human(const float x, const float y, const unsigned int max): Reactive(x, y, true, getCircle()), maxCount(max)
{
}

void Human::setMaxCount(const unsigned int max)
{
	this->maxCount = max;
}

unsigned Human::getCounter()
{
	if (this->counter) return --this->counter;
	else return (this->counter = this->maxCount);
}

b2Vec2 Human::getDirection() const
{
	return this->direction;
}

void Human::setDirection(const b2Vec2 vel)
{
	this->direction = vel;
}

float Human::getSpeed() const
{
	return this->speed;
}

void Human::setSpeed(float s)
{
	this->speed = speed;
}

Human::BodyList& Human::getBodies()
{
	return this->bodies;	
}

void Human::Zombify()
{
	this->zombified = true;
}

void Human::kill()
{
	this->killed = true;
}

bool Human::isDead()
{
	return this->killed;
}

Pointer::Pointer() : Object(0.f,0.f,true,new SGE::Circle(6.f))
{
}
