#include "Objects.hpp"
#include <sge_shape_rectangle.hpp>

glm::vec2 Player::getPosition() const noexcept
{
	auto bp = this->body->GetPosition();
	return glm::vec2(bp.x * 64.f, bp.y * 64.f);
}

void Player::setPosition(float x, float y)
{
	this->body->SetTransform(b2Vec2(x / 64.f, y / 64.f), this->body->GetAngle());
}

float Player::getX() const noexcept
{
	return this->body->GetPosition().x * 64.f;
}

float Player::getY() const noexcept
{
	return this->body->GetPosition().y * 64.f;
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

bool Human::isDead() const
{
	return this->killed;
}

glm::vec2 Human::getPosition() const noexcept
{
	auto bp = this->body->GetPosition();
	return glm::vec2(bp.x * 64.f, bp.y * 64.f);
}

void Human::setPosition(float x, float y)
{
	this->body->SetTransform(b2Vec2(x / 64.f, y / 64.f), this->body->GetAngle());
}

float Human::getX() const noexcept
{
	return this->body->GetPosition().x * 64.f;
}

float Human::getY() const noexcept
{
	return this->body->GetPosition().y * 64.f;
}

Pointer::Pointer() : Object(0.f,0.f,true,new SGE::Circle(6.f))
{
}
