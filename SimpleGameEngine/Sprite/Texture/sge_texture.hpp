#ifndef sge_texture_hpp
#define sge_texture_hpp

#include <string>
#include <GL/glew.h>

namespace SGE {

    struct GLTexture
    {
        GLuint id;
        unsigned int width;
        unsigned int height;
    };


    struct Texture
    {
        std::string path = "";
        GLTexture texture = {0,0,0};
    };
}
#endif
