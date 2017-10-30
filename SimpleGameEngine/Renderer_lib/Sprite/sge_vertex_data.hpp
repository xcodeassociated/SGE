//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_VERTEX_DATA_HPP
#define SGE_ZOMBIEGAME_SGE_VERTEX_DATA_HPP

namespace SGE {
    struct Position{
        float x;
        float y;
        Position(float _x, float _y);

        Position();

        ~Position();
    };

    struct Color{
        Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a);
        Color();

        ~Color();
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;

    };

    struct UV{
        float u, v;
        UV(float _u, float _v);

        UV();

        ~UV();
    };
}

#endif //SGE_ZOMBIEGAME_SGE_VERTEX_DATA_HPP
