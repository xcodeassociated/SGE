#ifndef sge_logic_collide_level_h
#define sge_logic_collide_level_h

#include "sge_logic_collide.hpp"
#include "sge_world_element.hpp"
#include <vector>

namespace SGE
{
	class Object;
	class Action;

    namespace Logics
	{
	    /**
         * \brief 
         */
        class BasicLevelCollider : public Collide
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

			std::vector<WorldElement>& objs;

        public:

	        /**
	         * \brief 
	         * \param objects 
	         * \param _onCollision 
	         */
	        BasicLevelCollider(std::vector<WorldElement>& objects, const collisionFunc& _onCollision);

	        /**
	         * \brief 
	         * \param _obj 
	         */
	        void performLogic(const ObjectBind& _obj) override;
        };
        
    }
}

#endif /* sge_logic_collide_level_h */
