//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_GLYPH_HPP
#define SGE_ZOMBIEGAME_SGE_GLYPH_HPP

#include "sge_vertex.hpp"

namespace SGE {

    struct Glyph {
        GLuint texture;
        float depth;

        Vertex topLeft;
        Vertex bottomLeft;
        Vertex topRight;
        Vertex bottomRight;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_GLYPH_HPP
