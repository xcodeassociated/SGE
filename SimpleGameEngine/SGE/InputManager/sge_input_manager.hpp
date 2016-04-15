//
//  sge_imput_manager.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 12.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_imput_manager_h
#define sge_imput_manager_h

#include "../include/sge_include.hpp"
#include <unordered_map>

namespace SGE {

    class InputManager{
        std::unordered_map<unsigned int, bool> keyMap;
        glm::vec2 mouseCoords;
        
    public:
        InputManager() : keyMap({}), mouseCoords(0.0f){
            
        };
        
        ~InputManager(){
            
        }
        
        void pressKey(unsigned int _keyID){
            this->keyMap[_keyID] = true;
        }
        
        void releaseKey(unsigned int _keyID){
            this->keyMap[_keyID] = false;
        }
        
        bool isKeyPressed(unsigned int _keyID){
            auto it = this->keyMap.find(_keyID);
            if (it != this->keyMap.end())
                return it->second;
            else
                return false;
        }
        
        void setMouseCoords(float x, float y){
            this->mouseCoords.x = x;
            this->mouseCoords.y = y;
        }
        
        glm::vec2 getMouseCoords() const {
            return this->mouseCoords;
        }
    };

}

#endif
