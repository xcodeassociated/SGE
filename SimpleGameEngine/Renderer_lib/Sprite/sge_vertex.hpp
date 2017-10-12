//
//  sge_vertex.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_vertex_h
#define sge_vertex_h

namespace SGE {

    struct Position{
        float x;
        float y;
        Position(float _x, float _y) : x(_x), y(_y){
        }
        Position(){
        }
        ~Position(){
        }
    };
    
    struct Color{
        Color (unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) : r(_r), g(_g), b(_b), a(_a){
        };
        Color(){
        }
        ~Color(){
        }
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
        
    };
    
    struct UV{
        float u, v;
        UV(float _u, float _v) : u(_u), v(_v){
        }
        UV(){
        }
        ~UV(){
        }
    };
    
    struct Vertex{
        Position position;
        Color color;
        UV uv;
        
        void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        }
        
        void setPosition(float x, float y){
            position.x = x;
            position.y = y;
        }
        void setUV(float u, float v){
            uv.u = u;
            uv.v = v;
        }
        
        Vertex(){
        }
        ~Vertex(){
        }
    };
    
};

#endif /* sge_vertex_h */
