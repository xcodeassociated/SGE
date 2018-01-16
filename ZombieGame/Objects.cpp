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

b2Vec2 Human::getVelocity() const
{
	return this->velocity;
}

void Human::setVelocity(const b2Vec2 vel)
{
	this->velocity = vel;
}

Human::BodyList& Human::getBodies()
{
	return this->bodies;	
}
