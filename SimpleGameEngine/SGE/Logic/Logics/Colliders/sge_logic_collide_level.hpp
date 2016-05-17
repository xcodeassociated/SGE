#ifndef sge_logic_collide_level_h
#define sge_logic_collide_level_h

#include "../sge_logic_collide.hpp"

namespace SGE {
    
    namespace Logics{
        
        class BasicLevelCollider : public Collide {
            std::vector<WorldElement>& objs;
            
        protected:
            ;;
            
        public:
            
            BasicLevelCollider(std::vector<WorldElement>& objects, collisionFunc _onCollision) : Collide(_onCollision), objs(objects) {}
            
            void performLogic(ObjectID _obj)
            {
                Object* oponent = _obj.getObject();
                Shape* selfShape = getBaseTileShape();
                Shape* oponentShape = oponent->getShape();
                
                bool collision = false;
                
                for(unsigned int i = 0; i < this->objs.size(); ++i)
                {
                    if (selfShape->getType() == oponentShape->getType())
                        collision = this->collideWithSameShape(&objs[i], oponent);
                    else
                        collision = this->collideWithDifferentShape(&objs[i], oponent);
                    
                    if (collision){
                        ActionID aid = this->onCollision(Object::ID(-1,&objs[i]), _obj);
                        action_handler->performSingleAction(std::make_pair(_obj, aid), (this->priority == LogicPriority::Highest) );
                    }
                }
            }
        };
        
    }
}

#endif /* sge_logic_collide_level_h */
