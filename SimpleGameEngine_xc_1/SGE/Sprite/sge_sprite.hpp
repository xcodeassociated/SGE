//
//  sprite.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 17.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sprite_h
#define sprite_h

#include "../include/sge_include.hpp"

namespace SGE {
    
    class Sprite{
        float x = 0, y = 0;
        float width = 0, height = 0;
        GLuint vboID = 0;
        
        bool isInit = false;
        
    public:
        Sprite(){
        
        };
        
        ~Sprite(){
            if (this->vboID != 0)
                glDeleteBuffers(1, &(this->vboID));
            
            std::cout << ">>    Sprite deleted!" << std::endl;
        };
        
        const bool isInited(){ return this->isInit; }
        
        void init(float _x, float _y, float _width, float _height){
            this->x = _x;
            this->y = _y;
            this->width = _width;
            this->height = _height;
            
            if (this->vboID == 0){
                float vertexData[12];

                //First triangle
                vertexData[0] = this->x + this->width;
                vertexData[1] = this->x + this->width;
                
                vertexData[2] = this->x;
                vertexData[3] = this->y + this->height;
                
                vertexData[4] = this->x;
                vertexData[5] = this->y;
                
                //Second triangle
                vertexData[6] = this->x;
                vertexData[7] = this->y;
                
                vertexData[8] = this->x + this->width;
                vertexData[9] = this->y;
                
                vertexData[10] = this->x + this->width;
                vertexData[11] = this->y + this->height;
                
                GLuint VertexArrayID;
                glGenVertexArrays(1, &VertexArrayID);
                glBindVertexArray(VertexArrayID);
                
                glGenBuffers(1, &this->vboID);
                glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                this->isInit = true;
            }
        };
        
        void draw(){
            glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
            glEnableVertexAttribArray(0);
            
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            
            glDisableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    };
    
}

#endif /* sprite_h */
