//
//  sge_action_move.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 06/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_action_move_h
#define sge_action_move_h

#include "../sge_action.hpp"
#include "../../ObjectManager/sge_action_handler.hpp"

namespace SGE {
    namespace ACTION {
        class Move : virtual public Action {
        
            float destX, destY;
            
        public:
            
            Move(float _x, float _y, double _duration) : Action(_duration), destX(_x), destY(_y) {
                ;
            }
            
        private:
            
            virtual void action_begin(Object* obj) noexcept override {
                ;
            }
            
            virtual void action_main(Object* obj) noexcept override {
                //TODO...
                
                //debug only:
                this->action_handler->foo();
                std::cout << obj->getX() << ' ' << obj->getY() << std::endl;
                obj->setPosition(obj->getX()+this->destX,obj->getY()+this->destY);
                std::cout << obj->getX() << ' ' << obj->getY() << std::endl;
            }
            
            virtual void action_ends(Object* obj) noexcept override {
                ;
            }
            
        public:
            void setObjectManager(ActionHandler* _action_handler) noexcept {
                this->action_handler = _action_handler;
            }
        };
    }
}

#endif /* sge_action_move_h */
