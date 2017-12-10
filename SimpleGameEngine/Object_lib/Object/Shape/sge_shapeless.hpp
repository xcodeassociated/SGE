//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_SHAPELESS_HPP
#define SGE_ZOMBIEGAME_SGE_SHAPELESS_HPP

#include "sge_shape.hpp"

namespace SGE
{
	/**
     * \brief 
     * \return 
     */
    Shape* getShapeless();

	/**
     * \brief 
     */
    class Shapeless : public Shape
    {
	    /**
         * \brief 
         */
        Shapeless();

    public:
        //Single Flyweight for no shape objects?
	    /**
         * \brief 
         * \return 
         */
        friend Shape* getShapeless();
    };

}


#endif //SGE_ZOMBIEGAME_SGE_SHAPELESS_HPP
