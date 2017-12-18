#include "Objects.hpp"
#include <sge_shape_circle.hpp>
#include <sge_shape_rectangle.hpp>

SGE::Shape* getCircle()
{
	static SGE::Circle c(32, false);
	return &c;
}

Player::Player(): SGE::Reactive(64, 64, true, getCircle())
{
}

Player::Player(const float x, const float y): SGE::Reactive(x, y, true, new SGE::Circle(32))
{
}

Portal::Portal(float x, float y): SGE::Reactive(x, y, true, new SGE::Rectangle(64, 64))
{
}

Human::Human(const float x, const float y): SGE::Being(x, y, true, getCircle())
{
}

Human::Human(const float x, const float y, const unsigned max): SGE::Being(x, y, true, getCircle()), maxCount(max)
{
}

void Human::setMaxCount(const unsigned max)
{
	this->maxCount = max;
}

unsigned Human::getCounter()
{
	if (this->counter) return --this->counter;
	else return (this->counter = this->maxCount);
}

glm::vec2 Human::getVelocity() const
{
	return this->velocity;
}

void Human::setVelocity(const glm::vec2 vel)
{
	this->velocity = vel;
}
