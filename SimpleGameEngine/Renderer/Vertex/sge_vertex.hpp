//
//  sge_vertex.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_vertex_h
#define sge_vertex_h

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
        virtual ~Color() = default;

        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;
        unsigned char a = 0;
    };

    struct UV
    {
        float u = 0;
        float v = 0;

        UV(float _u, float _v);
        UV() = default;
        virtual ~UV() = default;
    };

    struct Vertex
	{
        Position position;
        Color color;
        UV uv;

	    void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	    void setPosition(float x, float y);
	    void setUV(float u, float v);
    };
}

#endif /* sge_vertex_h */
