#ifndef sge_color_h
#define sge_color_h

namespace SGE
{
    struct Color
    {
		unsigned char r = 0;
		unsigned char g = 0;
		unsigned char b = 0;
		unsigned char a = 0;

        Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) 
            : r(_r), g(_g), b(_b), a(_a) {};

        Color() = default;
    };
}

#endif
