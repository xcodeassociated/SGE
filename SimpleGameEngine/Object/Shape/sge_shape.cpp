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
