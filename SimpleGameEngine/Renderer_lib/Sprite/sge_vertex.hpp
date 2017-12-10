//
//  sge_vertex.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_vertex_h
#define sge_vertex_h

#include "sge_vertex_data.hpp"

namespace SGE
{
	/**
     * \brief 
     */
    struct Vertex
	{
	    /**
         * \brief 
         */
        Position position;
	    /**
         * \brief 
         */
        Color color;
	    /**
         * \brief 
         */
        UV uv;

	    /**
	     * \brief 
	     * \param r 
	     * \param g 
	     * \param b 
	     * \param a 
	     */
	    void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	    /**
	     * \brief 
	     * \param x 
	     * \param y 
	     */
	    void setPosition(float x, float y);

	    /**
	     * \brief 
	     * \param u 
	     * \param v 
	     */
	    void setUV(float u, float v);

	    /**
	     * \brief 
	     */
	    Vertex();

	    /**
	     * \brief 
	     */
	    ~Vertex();
    };
    
}

#endif /* sge_vertex_h */
