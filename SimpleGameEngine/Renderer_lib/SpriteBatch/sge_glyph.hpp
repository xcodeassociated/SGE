//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_GLYPH_HPP
#define SGE_ZOMBIEGAME_SGE_GLYPH_HPP

#include "sge_vertex.hpp"

namespace SGE {

	/**
     * \brief 
     */
    struct Glyph {
	    /**
         * \brief 
         */
        GLuint texture;
	    /**
         * \brief 
         */
        float depth;

	    /**
         * \brief 
         */
        Vertex topLeft;
	    /**
         * \brief 
         */
        Vertex bottomLeft;
	    /**
         * \brief 
         */
        Vertex topRight;
	    /**
         * \brief 
         */
        Vertex bottomRight;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_GLYPH_HPP
