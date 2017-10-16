#ifndef sge_logic_collide_level_h
#define sge_logic_collide_level_h

#include "sge_logic_collide.hpp"
#include "sge_world_element.hpp"
#include <vector>

namespace SGE {
    
    namespace Logics{
        
        class BasicLevelCollider : public Collide {
            std::vector<WorldElement>& objs;
            
        protected:
            ;;
            
        public:

	        BasicLevelCollider(std::vector<WorldElement>& objects, collisionFunc _onCollision);

	        void performLogic(const ObjectBind& _obj) override;
        };
        
    }
}

#endif /* sge_logic_collide_level_h */
