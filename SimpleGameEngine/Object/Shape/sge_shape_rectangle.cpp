//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_shape_rectangle.hpp"


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