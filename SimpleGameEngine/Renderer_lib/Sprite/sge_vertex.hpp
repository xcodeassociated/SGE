//
//  sge_vertex.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_vertex_h
#define sge_vertex_h

#include "sge_vertex_data.hpp"

namespace SGE {
    
    struct Vertex{
        Position position;
        Color color;
        UV uv;

	    void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	    void setPosition(float x, float y);

	    void setUV(float u, float v);

	    Vertex();

	    ~Vertex();
    };
    
}

#endif /* sge_vertex_h */
