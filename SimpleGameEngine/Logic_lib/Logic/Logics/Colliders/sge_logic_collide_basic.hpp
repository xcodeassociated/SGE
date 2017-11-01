//
//  sge_logic_collide_basic.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 15/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_logic_collide_basic_h
#define sge_logic_collide_basic_h

#include "sge_logic_collide.hpp"

namespace SGE {
    
    namespace Logics{
        
	    /**
         * \brief 
         */
        class BasicCollider : public Collide {
	        /**
			 * \brief 
			 */
			ObjectID obj;
            
		public:

	        /**
	         * \brief 
	         * \param obj 
	         * \param _onCollision 
	         */
	        BasicCollider(Object::ID obj, collisionFunc _onCollision);

	        /**
	         * \brief 
	         * \param _obj 
	         */
	        virtual void performLogic(const ObjectBind& _obj) override;
        };
        
    }
}


#endif /* sge_logic_collide_basic_h */
