#ifndef sge_logic_collide_level_precise_h
#define sge_logic_collide_level_precise_h

#include "sge_logic_collide.hpp"
#include <sge_world_element.hpp>
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
			/**
			 * \brief 
			 */
			std::vector<WorldElement>& objs;

		public:
			/**
			 * \brief 
			 * \param objects 
			 */
			PreciseLevelCollider(std::vector<WorldElement>& objects);
			/**
			 * \brief 
			 * \param _obj 
			 */
			virtual void performLogic(const ObjectBind& _obj) override;
		};

	}
}

#endif /* sge_logic_collide_level_precise_h */
