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
    }

	void ObjectManager::InputHandler::mapAction(const ActionBinder& bind)
	{
		auto p = this->keyMap.insert(std::make_pair(bind.getKey(),bind.getBind()));
		if(!p.second) throw std::runtime_error("You are an idiot");
	}

	void ObjectManager::InputHandler::unmapAction(const ActionBinder& bind)
	{
		if(this->keyMap.erase(bind.getKey())==0) throw std::runtime_error("You are an idiot");
	}

	void ObjectManager::InputHandler::pressKey(Key k)
	{
		auto it = this->keyMap.find(k);
		if (it == this->keyMap.end()) return;
		this->manager->action_handler->handleInputAction(it->second);
	}

    void ObjectManager::InputHandler::operator()(void) noexcept {
        
		SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:{                
                    this->manager->windowClosing();
                }break;

				case SDL_KEYDOWN: {
					this->pressKey(Key(event.key.keysym.sym));
				}break;
            }
        }
        
    }

}

#endif /* sge_input_handler_h */
