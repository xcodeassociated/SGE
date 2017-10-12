#ifndef sge_logic_collide_level_h
#define sge_logic_collide_level_h

#include "sge_logic_collide.hpp"

namespace SGE {
    
    namespace Logics{
        
        class BasicLevelCollider : public Collide {
            std::vector<WorldElement>& objs;
            
        protected:
            ;;
            
        public:
            
            BasicLevelCollider(std::vector<WorldElement>& objects, collisionFunc _onCollision) : Collide(_onCollision), objs(objects) {}
            
            void performLogic(const ObjectBind& _obj) override
            {
                Object* oponent = _obj[0].getObject();
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
                        ActionID aid = this->onCollision(Object::ID(&objs[i]), _obj[0]);
						this->sendAction(_obj[0],aid);
                    }
                }
            }
        };
        
    }
}

#endif /* sge_logic_collide_level_h */
