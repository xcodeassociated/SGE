//
//  sge_logic_collide_basic.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 15/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_logic_collide_basic_h
#define sge_logic_collide_basic_h

#include "../sge_logic_collide.hpp"

namespace SGE {
    
    namespace Logics{
        
        class BasicCollider : Collide {
			ObjectID obj;
		public:
			BasicCollider(Object::ID obj): obj(obj) {}

			void performLogic(Object* obj)
			{
				Object* obj2 = this->obj.getObject();
			}
        };
        
    }
}


#endif /* sge_logic_collide_basic_h */
