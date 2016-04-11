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
        
            virtual void action_begin(void) noexcept {
                ;
            }
            
            virtual void action_main(void) noexcept {
                //TODO...
                
                //debug only:
                this->action_handler->foo();
            }
            
            virtual void action_ends(void) noexcept {
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
