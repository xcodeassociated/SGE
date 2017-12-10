//
//  sge_camera_handler.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 11/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_camera_handler_h
#define sge_camera_handler_h

#include "sge_object.hpp"
#include <glm/glm.hpp>
#include <utility>

namespace SGE
{

    class Camera2d;

	/**
     * \brief 
     */
    class CameraHandler {
	    /**
         * \brief 
         */
        Camera2d* camera = nullptr;
	    /**
	     * \brief 
	     */
	    int x = 0;
	    /**
	     * \brief 
	     */
	    int y = 0;
	    /**
	     * \brief 
	     */
	    double scale = .0f;

    public:
	    /**
         * \brief 
         */
        CameraHandler(std::pair<int, int>) noexcept;

	    /**
         * \brief 
         * \return 
         */
        Camera2d* getCamera();

	    /**
         * \brief 
         */
        void setScale(double) noexcept;

	    /**
         * \brief 
         */
        void setPosition(int, int) noexcept;

	    /**
         * \brief 
         */
        void setPosition(glm::vec2) noexcept;

	    /**
         * \brief 
         */
        void updateCamera(void) const noexcept;

	    /**
         * \brief 
         * \return 
         */
        const glm::mat4& getCameraMatrix(void) const noexcept;

	    /**
         * \brief 
         * \return 
         */
        glm::vec2 getScreenToWorld(glm::vec2) const noexcept;

	    /**
         * \brief 
         * \return 
         */
        glm::vec2 getScreenToWorld(int, int) const noexcept;

    };

}

#endif /* sge_camera_handler_h */
