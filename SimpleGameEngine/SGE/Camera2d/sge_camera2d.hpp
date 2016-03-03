//
//  sge_camera2d.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 11.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_camera2d_h
#define sge_camera2d_h

#include "../include/sge_include.hpp"

namespace SGE {
    
    class Camera2d{
        glm::vec2 position;
        glm::mat4 cameraMatrix;
        glm::mat4 orthoMatrix;
        float scale = 1.0f;
        bool matUpdate = false;
        int box[2];
        
    public:
        Camera2d(unsigned int _width, unsigned int _height) : position(0.f, 0.f), cameraMatrix(1.f), matUpdate(true){
            this->box[0] = _width;
            this->box[1] = _height;
            
            this->orthoMatrix = glm::ortho(0.0f, (float)this->box[0], 0.0f, (float)this->box[1]);
        }
        
        ~Camera2d(){
        }
        
        void setPosition(glm::vec2 _position){
            this->position = _position;
            this->matUpdate = true;
        }
        
        const glm::vec2 getPosition(){
            return this->position;
        }
        
        void setScale(float _scale){
            this->scale = _scale;
            this->matUpdate = true;
        }
        
        const float getScale(){
            return this->scale;
        }
        
        const glm::mat4 getCameraMatrix(){
            return this->cameraMatrix;
        }
        
        void update(){
            if (this->matUpdate){
                glm::vec3 translate( - this->position.x + (this->box[0] / 2),  - this->position.y + (this->box[1] / 2), 0.0f );
                this->cameraMatrix = glm::translate(this->orthoMatrix, translate);
                
                glm::vec3 scale_vec(this->scale, this->scale, 0.0f);
                this->cameraMatrix = glm::scale(glm::mat4(1.0f), scale_vec) * this->cameraMatrix;
                
                this->matUpdate = false;
            }
        }
        
        const glm::vec2 screenToWorld(glm::vec2 _screenCoords){
            //invert y axis
            _screenCoords.y = SCREEN_HEIGHT - _screenCoords.y;
            
            //0 is center & scaling & set position
            _screenCoords -= glm::vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            _screenCoords /= this->scale;
            _screenCoords += this->position;
            
            return _screenCoords;
        }
        
        
    };
    
}

#endif /* sge_camera2d_h */
