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
#include <functional>

namespace SGE
{
	class Action;
	class Object;

    namespace Logics
	{
	    /**
         * \brief 
         */
        class BasicCollider : public Collide
		{
		public:
			/**
			 * \brief
			 */
			using collisionFunc = std::function<Action*(Object*, Object*)>;

		private:
	        /**
			 * \brief 
			 */
			collisionFunc onCollision;

            Object* object_a = nullptr;
			Object* object_b = nullptr;

		public:

	        /**
	         * \brief 
	         * \param object
	         * \param _onCollision 
	         */
	        BasicCollider(Object* object_a, Object* object_b, const collisionFunc& _onCollision);

	        /**
	         * \brief 
	         * \param _obj 
	         */
	        virtual void performLogic() override;
        };
        
    }
}


#endif /* sge_logic_collide_basic_h */
