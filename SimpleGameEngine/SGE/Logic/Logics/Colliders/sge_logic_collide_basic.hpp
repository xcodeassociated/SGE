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
        
        class BasicCollider : public Collide {
			ObjectID obj;
            
        protected:
            ;;
            
		public:
            
			BasicCollider(Object::ID obj, collisionFunc _onCollision) : Collide(_onCollision), obj(obj) {}

			void performLogic(ObjectID _obj)
			{
				Object* self = this->obj.getObject();
                Object* oponent = _obj.getObject();
                
                Shape* selfShape = self->getShape();
                Shape* oponentShape = oponent->getShape();
                
                bool collision = false;
                
                if (selfShape->getType() == oponentShape->getType())
                    collision = this->collideWithSameShape(self, oponent);
                else
                    collision = this->collideWithDifferentShape(self, oponent);
                
                if (collision){
                    ActionID aid = this->onCollision(obj, _obj);
                    action_handler->performSingleAction(std::make_pair(_obj, aid), (this->priority == LogicPriority::Highest) );
                }
			}
        };
        
    }
}


#endif /* sge_logic_collide_basic_h */
