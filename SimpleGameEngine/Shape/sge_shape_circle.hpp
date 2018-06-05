//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_SHAPE_CIRCLE_HPP
#define SGE_ZOMBIEGAME_SGE_SHAPE_CIRCLE_HPP

#include "sge_shape.hpp"

namespace SGE
{
    class Circle : public Shape
    {
        float radius = 0.f;

    public:

        Circle();

        Circle(const Circle&) = default;
	
        Circle(float radius);

        Circle(float radius, bool disposable);

        float getRadius() const;

        void setRadius(float radius);
    };

}

#endif //SGE_ZOMBIEGAME_SGE_SHAPE_CIRCLE_HPP
