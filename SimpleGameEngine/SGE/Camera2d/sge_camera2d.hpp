//
//  sge_camera2d.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 11.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_camera2d_h
#define sge_camera2d_h

#include "../Object/sge_object.hpp"
#include "../include/sge_include.hpp"

namespace SGE {
    
    class Camera2d final : public Object{
        glm::mat4 cameraMatrix;
        glm::mat4 orthoMatrix;
        float scale = 1.0f;
        bool matUpdate = false;
        int box[2];
        
    public:
        Camera2d(unsigned int _width, unsigned int _height) : Object(0.f, 0.f), cameraMatrix(1.f), matUpdate(true){
            this->box[0] = _width;
            this->box[1] = _height;
            
            this->orthoMatrix = glm::ortho(0.0f, (float)this->box[0], 0.0f, (float)this->box[1]);
        }
        
        ~Camera2d(){
        }
        
        void setPosition(float x, float y){
            this->Object::setPosition(x,y);
            this->matUpdate = true;
        }
        
        void setPosition(glm::vec2 _position){
            this->Y = _position.y;
            this->X = _position.x;
            this->matUpdate = true;
        }
        
        glm::vec2 getPosition(){
            return glm::vec2{this->X,this->Y};
        }
        
        void setScale(float _scale){
            this->scale = _scale;
            this->matUpdate = true;
        }
        
        float getScale(){
            return this->scale;
        }
        
        const glm::mat4& getCameraMatrix(){
            return this->cameraMatrix;
        }
        
        void update(){
            if (this->matUpdate){
                glm::vec3 translate( - this->X + (this->box[0] / 2),  - this->Y + (this->box[1] / 2), 0.0f );
                this->cameraMatrix = glm::translate(this->orthoMatrix, translate);
                
                glm::vec3 scale_vec(this->scale, this->scale, 0.0f);
                this->cameraMatrix = glm::scale(glm::mat4(1.0f), scale_vec) * this->cameraMatrix;
                
                this->matUpdate = false;
            }
        }
        
    };
    
}

#endif /* sge_camera2d_h */
