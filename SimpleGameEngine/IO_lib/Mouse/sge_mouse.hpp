//
//  sge_mouse.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 20/07/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_mouse_h
#define sge_mouse_h

#include "sge_object.hpp"

namespace SGE {
    
    class MouseObject : public Object {
	    /**
          * \brief Mouse coordinates
          * /todo Inherited Object already has xy coordinates!
          */
         glm::vec2 mouseCoords;
        
    public:
	    /**
	     * \brief Default MouseObject constructor
	     */
	    MouseObject() noexcept;

	    /**
	     * \brief Sets MouseObject coordinates to coords
	     * \param coords 2D coordinates
	     */
	    void setMouseCoords(glm::vec2 coords) noexcept;

	    /**
	     * \brief Returns current coordinates
	     * \return Current MouseObjects Coordinates
	     */
	    glm::vec2 getMouseCoords(void) const noexcept;
    };
    
}

#endif /* sge_mouse_h */
