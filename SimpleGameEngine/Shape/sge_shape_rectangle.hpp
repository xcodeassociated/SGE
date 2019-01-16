//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_RECTANGLE_HPP
#define SGE_ZOMBIEGAME_SGE_RECTANGLE_HPP

#include "sge_shape.hpp"

namespace SGE
{
    class Rectangle : public Shape
    {
        float width = 0.f;
        float height = 0.f;

    public:
		Rectangle();
        Rectangle(const Rectangle&) = default;
        Rectangle(float width, float height);
        Rectangle(float width, float height, bool disposable);

        float getWidth() const;
        void setWidth(const float width);

        float getHeight() const;
        void setHeight(const float height);
    };

    Rectangle* getBaseTileShape();
}


#endif //SGE_ZOMBIEGAME_SGE_RECTANGLE_HPP
