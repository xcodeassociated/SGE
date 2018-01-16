#include "sge_reactive.hpp"

SGE::Reactive::Reactive(b2Body * body)
{
	this->setBody(body);
}

SGE::Reactive::Reactive(float x, float y, b2Body* body) : Object(x,y)
{
	this->setBody(body);
}

SGE::Reactive::Reactive(float x, float y, bool draw, b2Body* body) : Object(x,y,draw)
{
	this->setBody(body);
}

void SGE::Reactive::setBody(b2Body* b2Body)
{
	this->body = b2Body;
	this->body->SetTransform(b2Vec2(this->X, this->Y), this->body->GetAngle());
	this->body->SetUserData(this);
}

b2Body* SGE::Reactive::getBody()
{
	return this->body;
}

const b2Body* SGE::Reactive::getBody() const
{
	return this->body;
}

glm::vec2 SGE::Reactive::getPosition() const noexcept
{
	auto pos = this->body->GetPosition();
	return glm::vec2(pos.x, pos.y);
}

void SGE::Reactive::setPosition(float x, float y)
{
	this->body->SetTransform(b2Vec2(x, y), this->body->GetAngle());
}

float SGE::Reactive::getX() const noexcept
{
	return this->body->GetPosition().x;
}

float SGE::Reactive::getY() const noexcept
{
	return this->body->GetPosition().y;
}

b2Fixture* SGE::Reactive::addFixture(const b2FixtureDef& fixtureDef)
{
	b2Fixture* fixture = this->body->CreateFixture(&fixtureDef);
	fixture->SetUserData(this);
	return fixture;
}

b2Fixture* SGE::Reactive::addFixture(const b2Shape& shape)
{
	b2Fixture* fixture = this->body->CreateFixture(&shape, 0);
	fixture->SetUserData(this);
	return fixture;
}
