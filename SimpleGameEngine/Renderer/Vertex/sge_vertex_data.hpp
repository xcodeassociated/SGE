//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_VERTEX_DATA_HPP
#define SGE_ZOMBIEGAME_SGE_VERTEX_DATA_HPP

namespace SGE
{
    struct Position
	{
        float x = 0;
        float y = 0;

        Position(float _x, float _y);
		Position() = default;
    };

    struct Color
	{

		Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a);
		Color() = default;
		~Color() = default;

        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

    struct UV
	{
	    float u;
	    float v;
	
        UV(float _u, float _v);
		UV() = default;
		~UV() = default;
    };
}

#endif //SGE_ZOMBIEGAME_SGE_VERTEX_DATA_HPP
