#ifndef sge_logic_collide_level_precise_h
#define sge_logic_collide_level_precise_h

#include "sge_logic_collide.hpp"
#include <sge_world_element.hpp>
#include <vector>

namespace SGE {

	namespace Logics {

		class PreciseLevelCollider : public Collide {
			std::vector<WorldElement>& objs;
		protected:
			;;

		public:
			PreciseLevelCollider(std::vector<WorldElement>& objects);

			void performLogic(const ObjectBind& _obj) override;
		};

	}
}

#endif /* sge_logic_collide_level_precise_h */
