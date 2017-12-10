//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_VERTEX_DATA_HPP
#define SGE_ZOMBIEGAME_SGE_VERTEX_DATA_HPP

namespace SGE
{
	/**
     * \brief 
     */
    struct Position
	{
	    /**
         * \brief 
         */
        float x;
	    /**
         * \brief 
         */
        float y;
	    /**
         * \brief 
         * \param _x 
         * \param _y 
         */
        Position(float _x, float _y);

	    /**
         * \brief 
         */
        Position();

	    /**
         * \brief 
         */
        ~Position();
    };

	/**
     * \brief 
     */
    struct Color
	{
	    /**
         * \brief 
         * \param _r 
         * \param _g 
         * \param _b 
         * \param _a 
         */
        Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a);
	    /**
         * \brief 
         */
        Color();

        ~Color();
	    /**
         * \brief 
         */
        unsigned char r;
	    /**
         * \brief 
         */
        unsigned char g;
	    /**
         * \brief 
         */
        unsigned char b;
	    /**
         * \brief 
         */
        unsigned char a;

    };

	/**
     * \brief 
     */
    struct UV
	{
	    /**
	     * \brief 
	     */
	    float u;
	    /**
	     * \brief 
	     */
	    float v;
	    /**
         * \brief 
         * \param _u 
         * \param _v 
         */
        UV(float _u, float _v);

	    /**
         * \brief 
         */
        UV();

	    /**
         * \brief 
         */
        ~UV();
    };
}

#endif //SGE_ZOMBIEGAME_SGE_VERTEX_DATA_HPP
