#ifndef sge_logic_move_h
#define sge_logic_move_h

#include "sge_logic.hpp"
#include "sge_action_handler.hpp"
#include "sge_key.hpp"

namespace SGE
{
	namespace Logics
	{
		class SimpleMove : public Logic
		{
			float speed = 0;
			const Key up, down, left, right;
		public:
			SimpleMove(const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right);
			~SimpleMove() = default;

			void performLogic(const ObjectBind& obj) override;
		};
	}
}

#endif //!sge_logic_move_h
