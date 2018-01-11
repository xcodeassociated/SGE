#include "sge_object.hpp"

SGE::Object::Object(float x, float y): X(x), Y(y)
{
}

SGE::Object::Object(float x, float y, Shape* shape): X(x), Y(y), shape(shape)
{
}

SGE::Object::Object(float x, float y, bool draw): X(x), Y(y), drawable(draw)
{
}

SGE::Object::Object(float x, float y, bool draw, Shape* shape): X(x), Y(y), drawable(draw), shape(shape)
{
}

SGE::Object::~Object()
{
	if (this->shape->isDisposable()) delete this->shape;
}

float SGE::Object::getX() const noexcept
{
	return this->X;
}

float SGE::Object::getY() const noexcept
{
	return this->Y;
}

void SGE::Object::setDrawable(bool e) noexcept
{
	this->drawable = e;
}

bool SGE::Object::getDrawable() const noexcept
{
	return this->drawable;
}

void SGE::Object::setPosition(float x, float y)
{
	this->X = x;
	this->Y = y;
}

glm::vec2 SGE::Object::getPosition() const noexcept
{
	return glm::vec2(this->X, this->Y);
}

SGE::Shape* SGE::Object::getShape() noexcept
{
	return this->shape;
}

SGE::LogicPriority SGE::Object::getLock() const noexcept
{
	return lock;
}

void SGE::Object::setLock(const LogicPriority& lock) noexcept
{
	this->lock = lock;
}

SGE::VoidObject::VoidObject(): Object()
{
}

