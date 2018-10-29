#include "sge_object.hpp"

SGE::Object::Object(float x, float y): Object(b2Vec2{x,y})
{}

SGE::Object::Object(b2Vec2 position) : position(position)
{}

SGE::Object::Object(b2Vec2 position, Shape* shape) : position(position), shape(shape)
{}

SGE::Object::Object(b2Vec2 position, bool draw) : position{position}, drawable(draw)
{}

SGE::Object::Object(b2Vec2 position, bool draw, Shape* shape) : position(position), shape(shape), drawable(draw)
{}

SGE::Object::Object(float x, float y, Shape* shape) : Object(b2Vec2{x,y}, shape)
{}

SGE::Object::Object(float x, float y, bool draw) : Object(b2Vec2{x,y}, draw)
{}

SGE::Object::Object(float x, float y, bool draw, Shape* shape) : Object(b2Vec2{x,y}, draw, shape)
{}

SGE::Object::~Object()
{
	if(this->shape->isDisposable()) delete this->shape;
}

void SGE::Object::setDrawable(bool b) noexcept
{
	this->drawable = b;
}

bool SGE::Object::getDrawable() const noexcept
{
	return this->drawable;
}

void SGE::Object::setVisible(bool b) noexcept
{
	this->visible = b;
}

bool SGE::Object::getVisible() const noexcept
{
	return this->visible;
}

b2Vec2 SGE::Object::getPosition() const noexcept
{
	return this->position;
}

glm::vec2 SGE::Object::getPositionGLM() const noexcept
{
	return glm::vec2(this->position.x * 64.f, this->position.y * 64.f);
}

float SGE::Object::getX() const noexcept
{
	return this->position.x;
}

float SGE::Object::getXGLM() const noexcept
{
	return this->position.x*64.f;
}

float SGE::Object::getY() const noexcept
{
	return this->position.y;
}

float SGE::Object::getYGLM() const noexcept
{
	return this->position.y * 64.f;
}

void SGE::Object::setPosition(b2Vec2 pos)
{
	this->position = pos;
}

void SGE::Object::setPositionGLM(float x, float y)
{
	this->position = b2Vec2{x / 64.f, y / 64.f};
}

void SGE::Object::setPositionGLM(glm::vec2 pos)
{
	this->position = b2Vec2{pos.x / 64.f, pos.y / 64.f};
}

SGE::Shape* SGE::Object::getShape() noexcept
{
	return this->shape;
}

void SGE::Object::setShape(Shape* newShape) noexcept
{
	if(this->shape->isDisposable())
	{
		delete this->shape;
	}
	this->shape = newShape;
}

SGE::LogicPriority SGE::Object::getLock() const noexcept
{
	return lock;
}

void SGE::Object::setLock(const LogicPriority& lock) noexcept
{
	this->lock = lock;
}

void SGE::Object::setTextured(bool b)
{
	this->textured = b;
}

bool SGE::Object::isTextured() const
{
	return this->textured;
}

SGE::VoidObject::VoidObject(): Object()
{}

float SGE::Object::getOrientation() const
{
	return orientation;
}

void SGE::Object::setOrientation(float orientation)
{
	this->orientation = orientation;
}

SGE::GLTexture SGE::Object::getTexture() const
{
	return this->texture;
}

void SGE::Object::setTexture(GLTexture texture)
{
	this->texture = texture;
}
