//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_SHAPE_CIRCLE_HPP
#define SGE_ZOMBIEGAME_SGE_SHAPE_CIRCLE_HPP

#include "sge_shape.hpp"

namespace SGE
{
	/**
     * \brief 
     */
    class Circle : public Shape
    {
    private:
	    /**
         * \brief 
         */
        float radius = 0.f;

    public:
	    /**
         * \brief 
         */
        Circle();
	    /**
         * \brief 
         */
        Circle(const Circle&) = default;
	    /**
         * \brief 
         * \param radius 
         */
        explicit Circle(float radius);
	    /**
         * \brief 
         * \param radius 
         * \param disposable 
         */
        Circle(float radius, bool disposable);

	    /**
         * \brief 
         * \return 
         */
        float getRadius() const;

	    float getHeight() const override;
		float getWidth() const override;

	    /**
         * \brief 
         * \param radius 
         */
        void setRadius(float radius);
    };

}

#endif //SGE_ZOMBIEGAME_SGE_SHAPE_CIRCLE_HPP
