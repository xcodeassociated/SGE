#ifndef sge_logic_collide_level_precise_h
#define sge_logic_collide_level_precise_h

#include "sge_logic_collide.hpp"
#include "../../../Object/WorldElement/sge_world_element.hpp"
#include <vector>
#include <iostream>

namespace SGE
{
	namespace Logics
	{
		/**
		 * \brief 
		 */
		class PreciseLevelCollider : public Collide
		{
            Object* object = nullptr;

			/**
			 * \brief 
			 */
			std::vector<WorldElement>& objs;

		public:
			/**
			 * \brief 
			 * \param objects 
			 */
			PreciseLevelCollider(Object* object, std::vector<WorldElement>& objects);
			/**
			 * \brief 
			 * \param _obj 
			 */
			virtual void performLogic() override;
		};

	}
}

#endif /* sge_logic_collide_level_precise_h */
