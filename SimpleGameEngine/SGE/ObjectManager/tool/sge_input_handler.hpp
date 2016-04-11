//
//  sge_input_handler.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 11/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_input_handler_h
#define sge_input_handler_h

namespace SGE {
    
    ObjectManager::InputHandler::InputHandler(ObjectManager* m) noexcept : manager(m), input_manager(new InputManager) {
        ;
    }
    
    void ObjectManager::InputHandler::operator()(void) noexcept {
        
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:{
                    
                    this->manager->windowClosing();
                    
                }break;
            }
        }
        
    }

}

#endif /* sge_input_handler_h */
