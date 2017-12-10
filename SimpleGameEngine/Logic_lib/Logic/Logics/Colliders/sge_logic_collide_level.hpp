#ifndef sge_logic_collide_level_h
#define sge_logic_collide_level_h

#include "sge_logic_collide.hpp"
#include "sge_world_element.hpp"
#include <vector>

namespace SGE
{
    namespace Logics
	{
	    /**
         * \brief 
         */
        class BasicLevelCollider : public Collide {
	        /**
             * \brief 
             */
            std::vector<WorldElement>& objs;
            
        public:

	        /**
	         * \brief 
	         * \param objects 
	         * \param _onCollision 
	         */
	        BasicLevelCollider(std::vector<WorldElement>& objects, collisionFunc _onCollision);

	        /**
	         * \brief 
	         * \param _obj 
	         */
	        void performLogic(const ObjectBind& _obj) override;
        };
        
    }
}

#endif /* sge_logic_collide_level_h */
