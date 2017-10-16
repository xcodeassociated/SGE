#include "sge_shape.hpp"

SGE::Shape::Shape(ShapeType type): type(type)
{
}

SGE::Shape::Shape(ShapeType type, bool disposable): type(type), disposable(disposable)
{
}

SGE::Shape::~Shape()
{
}

SGE::ShapeType SGE::Shape::getType() const
{
	return this->type;
}

bool SGE::Shape::isDisposable()
{
	return this->disposable;
}

SGE::Shapeless::Shapeless(): Shape(ShapeType::None, false)
{
}

SGE::Circle::Circle(): Shape(ShapeType::Circle)
{
}

SGE::Circle::Circle(float radius): Shape(ShapeType::Circle), radius(radius)
{
}

SGE::Circle::Circle(float radius, bool disposable): Shape(ShapeType::Circle, disposable), radius(radius)
{
}

float SGE::Circle::getRadius() const
{
	return this->radius;
}

void SGE::Circle::setRadius(float radius)
{
	this->radius = radius;
}

SGE::Rectangle::Rectangle(): Shape(ShapeType::Rectangle)
{
}

SGE::Rectangle::Rectangle(float width, float height): Shape(ShapeType::Rectangle), width(width), height(height)
{
}

SGE::Rectangle::Rectangle(float width, float height, bool disposable): Shape(ShapeType::Rectangle, disposable), width(width), height(height)
{
}

float SGE::Rectangle::getWidth() const
{
	return width;
}

void SGE::Rectangle::setWidth(const float width)
{
	this->width = width;
}

float SGE::Rectangle::getHeight() const
{
	return height;
}

void SGE::Rectangle::setHeight(const float height)
{
	this->height = height;
}

SGE::Rectangle* SGE::getBaseTileShape()
{
	static Rectangle tile(64, 64, 0);
	return &tile;
}

SGE::Shape* SGE::getShapeless()
{
	static Shapeless s;
	return &s;
}
