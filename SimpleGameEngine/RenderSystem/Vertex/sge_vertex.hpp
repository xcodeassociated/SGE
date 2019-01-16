//
//  sge_vertex.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_vertex_h
#define sge_vertex_h

#include "Position/sge_position.hpp"
#include "Color/sge_color.hpp"
#include "../UV/sge_uv.hpp"

namespace SGE
{
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
