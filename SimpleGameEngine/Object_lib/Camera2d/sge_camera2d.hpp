//
//  sge_camera2d.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 11.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_camera2d_h
#define sge_camera2d_h

#include "sge_object.hpp"
#include <glm/mat4x4.hpp>

namespace SGE {
    
    class Camera2d final : public Object{
        glm::mat4 cameraMatrix;
        glm::mat4 orthoMatrix;
        float scale = 1.0f;
        bool matUpdate = false;
        int box[2];
        
    public:
	    Camera2d(unsigned int _width, unsigned int _height);

	    ~Camera2d();

	    void setPosition(float x, float y) override;

	    void setPosition(glm::vec2 _position);

	    glm::vec2 getPosition() const noexcept override;

	    void setScale(float _scale);

	    float getScale() const;

	    const glm::mat4& getCameraMatrix() const;

	    void update();
    };
    
}

#endif /* sge_camera2d_h */
