//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_RECTANGLE_HPP
#define SGE_ZOMBIEGAME_SGE_RECTANGLE_HPP

#include "sge_shape.hpp"

namespace SGE
{
	/**
     * \brief 
     */
    class Rectangle : public Shape
    {
    private:
	    /**
         * \brief 
         */
        float width = 0.f;
	    /**
         * \brief 
         */
        float height = 0.f;

    public:
	    /**
         * \brief 
         */
        Rectangle();
	    /**
         * \brief 
         */
        Rectangle(const Rectangle&) = default;
	    /**
         * \brief 
         * \param width 
         * \param height 
         */
        explicit Rectangle(float width, float height);
	    /**
         * \brief 
         * \param width 
         * \param height 
         * \param disposable 
         */
        Rectangle(float width, float height, bool disposable);

	    /**
         * \brief 
         * \return 
         */
        float getWidth() const;

	    /**
         * \brief 
         * \param width 
         */
        void setWidth(const float width);

	    /**
         * \brief 
         * \return 
         */
        float getHeight() const;

	    /**
         * \brief 
         * \param height 
         */
        void setHeight(const float height);
    };

	/**
     * \brief 
     * \return 
     */
    Rectangle* getBaseTileShape();

}


#endif //SGE_ZOMBIEGAME_SGE_RECTANGLE_HPP
