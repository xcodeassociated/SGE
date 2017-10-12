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
#include "sge_include.hpp"

namespace SGE {
    
    class MouseObject : public Object {
         glm::vec2 mouseCoords;
        
    public:
        MouseObject() noexcept : mouseCoords(0.0f, 0.0f) {}
        
        void setMouseCoords(glm::vec2 coords) noexcept {
            this->mouseCoords = coords;
        }
        
        glm::vec2 getMouseCoords(void) const noexcept {
            return this->mouseCoords;
        }
    };
    
}

#endif /* sge_mouse_h */
