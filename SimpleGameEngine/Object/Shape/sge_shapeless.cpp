//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_shapeless.hpp"

SGE::Shape* SGE::getShapeless()
{
    static Shapeless s;
    return &s;
}

SGE::Shapeless::Shapeless(): Shape(ShapeType::None, false)
{
}

float SGE::Shapeless::getWidth() const
{
	return 0.f;
}

float SGE::Shapeless::getHeight() const
{
	return 0.f;
}
