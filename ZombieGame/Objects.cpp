#include "Objects.hpp"
#include <sge_shape_circle.hpp>
#include <sge_shape_rectangle.hpp>
#include "Dynamics/b2Fixture.h"

SGE::Shape* getCircle()
{
	static SGE::Circle c(32, false);
	return &c;
}


glm::vec2 Physical::getPosition() const noexcept
{	
	auto pos = this->body->GetPosition();
	return glm::vec2(pos.x,pos.y);
}

void Physical::setPosition(float x, float y)
{
	this->body->SetTransform(b2Vec2(x, y),this->body->GetAngle());
}

float Physical::getX() const noexcept
{
	return this->body->GetPosition().x;
}

float Physical::getY() const noexcept
{
	return this->body->GetPosition().y;
}

Player::Player(): Physical(64, 64, true, getCircle())
{
}

Player::Player(const float x, const float y): Physical(x, y, true, new SGE::Circle(32))
{
}

void Physical::setBody(b2Body* b2Body)
{
	this->body = b2Body;
	this->body->SetTransform(b2Vec2(this->X, this->Y), this->body->GetAngle());
	this->body->SetUserData(this);
}

void Physical::addFixture(const b2FixtureDef& fixtureDef)
{
	b2Fixture* fixture = this->body->CreateFixture(&fixtureDef);
	fixture->SetUserData(this);
}

void Physical::addFixture(const b2Shape& shape)
{
	b2Fixture* fixture = this->body->CreateFixture(&shape,0);
	fixture->SetUserData(this);
}

Portal::Portal(float x, float y): SGE::Reactive(x, y, true, new SGE::Rectangle(64, 64))
{
}

Human::Human(const float x, const float y): Physical(x, y, true, getCircle())
{
}

Human::Human(const float x, const float y, const unsigned max): Physical(x, y, true, getCircle()), maxCount(max)
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
