//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_RENDER_BATCH_HPP
#define SGE_ZOMBIEGAME_SGE_RENDER_BATCH_HPP

#include <GL/glew.h>

namespace SGE
{
	/**
     * \brief 
     */
    class RenderBatch
    {
    public:
	    /**
         * \brief 
         * \param Offset 
         * \param NumVertices 
         * \param Texture 
         */
        RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) {
        }
	    /**
         * \brief 
         */
        GLuint offset;
	    /**
         * \brief 
         */
        GLuint numVertices;
	    /**
         * \brief 
         */
        GLuint texture;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_RENDER_BATCH_HPP
