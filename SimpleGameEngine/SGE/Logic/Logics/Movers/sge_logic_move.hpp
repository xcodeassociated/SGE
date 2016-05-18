#ifndef sge_logic_move_h
#define sge_logic_move_h

#include "../../sge_logic.hpp"

namespace SGE
{
	namespace Logics
	{
		class SimpleMove : public Logic
		{
			float speed = 0;
			const Key up, down, left, right;
		public:
			SimpleMove(const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right)
				:Logic(LogicPriority::Highest), speed(speed), up(up), down(down), left(left), right(right) {}
			~SimpleMove() = default;

			void performLogic(SGE::Object::ID obj) override
			{
				glm::vec2 move = { 0,0 };
				if (isPressed(this->up)) move.y += this->speed;
				if (isPressed(this->down)) move.y -= this->speed;
				if (isPressed(this->right)) move.x += this->speed;
				if (isPressed(this->left)) move.x -= this->speed;
				this->sendAction(obj, SGE::Action::ID(0, new SGE::ACTION::Move(move.x, move.y, 0)));
			}
		};
	}
}

#endif