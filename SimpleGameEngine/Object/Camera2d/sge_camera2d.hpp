//
//  sge_camera2d.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 11.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_camera2d_h
#define sge_camera2d_h

#include "../sge_object.hpp"
#include <glm/mat4x4.hpp>

namespace SGE
{
    
	/**
     * \brief 
     */
    class Camera2d final : public Object
	{
	    /**
         * \brief 
         */
        glm::mat4 cameraMatrix;
	    /**
         * \brief 
         */
        glm::mat4 orthoMatrix;
	    /**
         * \brief 
         */
        float scale = 1.0f;
	    /**
         * \brief 
         */
        bool matUpdate = false;
	    /**
         * \brief 
         */
        int box[2];
        
    public:
	    /**
	     * \brief 
	     * \param _width 
	     * \param _height 
	     */
	    Camera2d(unsigned int _width, unsigned int _height);

	    /**
	     * \brief 
	     */
	    ~Camera2d();

	    /**
	     * \brief 
	     * \param x 
	     * \param y 
	     */
	    void setPositionGLM(float x, float y) override;

	    /**
	     * \brief 
	     * \param _position 
	     */
	    void setPosition(glm::vec2 _position);

	    /**
	     * \brief 
	     * \param _scale 
	     */
	    void setCameraScale(float _scale);

	    /**
	     * \brief 
	     * \return 
	     */
	    float getCameraScale() const;

	    /**
	     * \brief 
	     * \return 
	     */
	    const glm::mat4& getCameraMatrix() const;

	    /**
	     * \brief 
	     */
	    void update();

	    glm::vec2 screenToWorld(glm::vec2 vec);
		int getWidth() const;
		int getHeight() const;
    };
    
}

#endif /* sge_camera2d_h */
