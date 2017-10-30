//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_shape_circle.hpp"

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