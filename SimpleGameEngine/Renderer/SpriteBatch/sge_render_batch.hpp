//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_RENDER_BATCH_HPP
#define SGE_ZOMBIEGAME_SGE_RENDER_BATCH_HPP

#include <GL/glew.h>

namespace SGE
{
    class RenderBatch
    {
    public:
        RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) {}

        GLuint offset = 0;

        GLuint numVertices = 0;

        GLuint texture = 0;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_RENDER_BATCH_HPP
