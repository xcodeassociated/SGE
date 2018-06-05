#include "sge_sprite.hpp"

SGE::Sprite::Sprite(float x, float y): X(x), Y(y)
{
}

SGE::Sprite::Sprite(float x, float y, Texture* texture) : X(x), Y(y), texture(texture)
{
}

SGE::Sprite::Sprite(float x, float y, Shape* shape): X(x), Y(y), shape(shape)
{
}

SGE::Sprite::Sprite(float x, float y, Shape* shape, Texture* texture): X(x), Y(y), shape(shape), texture(texture)
{
}

SGE::Sprite::Sprite(float x, float y, bool draw): X(x), Y(y), drawable(draw)
{
}

SGE::Sprite::Sprite(float x, float y, bool draw, Shape* shape): X(x), Y(y), drawable(draw), shape(shape)
{
}

SGE::Sprite::~Sprite()
{
	if (this->shape->isDisposable()) 
		delete this->shape;
}

float SGE::Sprite::getX() const noexcept
{
	return this->X;
}

float SGE::Sprite::getY() const noexcept
{
	return this->Y;
}

void SGE::Sprite::setDrawable(bool b) noexcept
{
	this->drawable = b;
}

bool SGE::Sprite::getDrawable() const noexcept
{
	return this->drawable;
}

void SGE::Sprite::setVisible(bool b) noexcept
{
	this->visible = b;
}

bool SGE::Sprite::getVisible() const noexcept
{
	return this->visible;
}

void SGE::Sprite::setPosition(float x, float y)
{
	this->X = x;
	this->Y = y;
}

glm::vec2 SGE::Sprite::getPosition() const noexcept
{
	return glm::vec2(this->X, this->Y);
}

SGE::Shape* SGE::Sprite::getShape() const noexcept
{
	return this->shape;
}

SGE::Texture* SGE::Sprite::getTexture() const noexcept
{
	return this->texture;
}

void SGE::Sprite::setTeexture(Texture* texture) noexcept
{
	this->texture = texture;
}


SGE::VoidSprite::VoidSprite() : Sprite()
{
}

