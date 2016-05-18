//
//  sge_logic_collide_group.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 01/05/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_logic_collide_group_h
#define sge_logic_collide_group_h

#include "../sge_logic_collide.hpp"

namespace SGE {
    
    namespace Logics{
        
        class BasicColliderGroup : public Collide {
            std::vector<ObjectID> objs;
            
        protected:
            ;;
            
        public:
            
            BasicColliderGroup(std::vector<ObjectID> objects, collisionFunc _onCollision) : Collide(_onCollision), objs(objects) {}
            
            void performLogic(ObjectID _obj)
            {
                ObjectID current(0,nullptr);
                Object* self = nullptr;
                Object* oponent = _obj.getObject();
                
                Shape* selfShape = nullptr;
                Shape* oponentShape = oponent->getShape();
                
                bool collision = false;
                
                for(unsigned int i = 0; i < this->objs.size(); ++i)
                {
                    current = this->objs[i];
                    self = current.getObject();
                    selfShape = self->getShape();
                    if (selfShape->getType() == oponentShape->getType())
                        collision = this->collideWithSameShape(self, oponent);
                    else
                        collision = this->collideWithDifferentShape(self, oponent);
                    
                    if (collision){
                        ActionID aid = this->onCollision(current, _obj);
						sendAction(current, aid);
                    }
                }
            }
        };
        
    }
}

#endif /* sge_logic_collide_group_h */
