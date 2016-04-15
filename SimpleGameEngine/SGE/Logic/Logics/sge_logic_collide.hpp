//
//  sge_logic_collide.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 15/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_logic_collide_h
#define sge_logic_collide_h

#include "../sge_logic.hpp"

namespace SGE {
    class Object;
    class ObjectID;
    
    namespace Logics{
        
        class Collide : public Logic{
        protected:
            
            Object* getObjectPointer(ObjectID) {
                return nullptr;
            }
        };
        
    }
}

#endif /* sge_logic_collide_h */
