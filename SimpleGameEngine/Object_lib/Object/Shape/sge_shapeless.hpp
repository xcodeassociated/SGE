//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_SHAPELESS_HPP
#define SGE_ZOMBIEGAME_SGE_SHAPELESS_HPP

#include "sge_shape.hpp"

namespace SGE {

    Shape* getShapeless();

    class Shapeless : public Shape
    {
        Shapeless();

    public:
        //Single Flyweight for no shape objects?
        friend Shape* getShapeless();
    };

}


#endif //SGE_ZOMBIEGAME_SGE_SHAPELESS_HPP
