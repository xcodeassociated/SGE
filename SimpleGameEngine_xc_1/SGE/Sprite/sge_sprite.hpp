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
#include "sge_vertex.hpp"
#include "../TextureLoader/sge_glTexture.hpp"
#include "../ResourceManager/sge_resource_manager.hpp"

namespace SGE {
    
    class Sprite{
        float x = 0, y = 0;
        float width = 0, height = 0;
        GLuint vboID = 0;
        
        bool isInit = false;
                
        SGE::GLTexture sampleTexture;
        SGE::ResourceManager* resourceManager = nullptr;
        
    public:
        Sprite() : resourceManager(SGE::ResourceManager::getSingleton()){
            std::cout << ">>>> Sprite Added!" << std::endl;
        };
        
        ~Sprite(){
            if (this->vboID != 0)
                glDeleteBuffers(1, &(this->vboID));
            
            delete this->resourceManager;
            
            std::cout << ">>>>    Sprite deleted!" << std::endl;
        };
        
        const bool isInited(){
            return this->isInit;
        }
        
        void init(float _x, float _y, float _width, float _height, const char* _filePath){
            this->x = _x;
            this->y = _y;
            this->width = _width;
            this->height = _height;
            
            this->sampleTexture = this->resourceManager->getTexture(_filePath);
            
            if (this->vboID == 0)
                glGenBuffers(1, &this->vboID);

            SGE::Vertex vertexData[6];

            //First triangle
            vertexData[0].setPosition(this->x + this->width, this->x + this->width);
            vertexData[0].setUV(1.0f, 1.0f);
            
            vertexData[1].setPosition(this->x, this->y + this->height);
            vertexData[1].setUV(0.0f, 1.0f);
            
            vertexData[2].setPosition(this->x, this->y);
            vertexData[2].setUV(0.0f, 0.0f);
            
            //Second triangle
            vertexData[3].setPosition(this->x, this->y);
            vertexData[3].setUV(0.0f, 0.0f);
            
            vertexData[4].setPosition(this->x + this->width, this->y);
            vertexData[4].setUV(1.0f, 0.0f);
            
            vertexData[5].setPosition(this->x + this->width, this->y + this->height);
            vertexData[5].setUV(1.0f, 1.0f);
            
            for (int i = 0; i < 6; i++)
                vertexData[i].setColor(255, 255, 255, 255); //vertexData[i].setColor(255, 0, 255, 255);
            
            
            //vertexData[1].setColor(0, 0, 255, 255);
            //vertexData[4].setColor(0, 255, 0, 255);

            glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            this->isInit = true;
            
        };
        
        void draw(){
            glBindTexture(GL_TEXTURE_2D, this->sampleTexture.id);
            
            glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
            glEnableVertexAttribArray(0);
            
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(SGE::Vertex), (void*)offsetof(SGE::Vertex, position));
            glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(SGE::Vertex), (void*)offsetof(SGE::Vertex, color));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SGE::Vertex), (void*)offsetof(SGE::Vertex, uv));
            
            glDrawArrays(GL_TRIANGLES, 0, 6);
            
            glDisableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    };
    
}

#endif /* sprite_h */
