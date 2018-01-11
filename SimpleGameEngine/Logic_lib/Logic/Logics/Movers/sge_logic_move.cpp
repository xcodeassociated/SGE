#include "sge_logic_move.hpp"
#include <sge_action_move.hpp>
#include <sge_keyboard_state.hpp>
#include <sge_fps_limiter.hpp>

SGE::Logics::SimpleMove::SimpleMove(Object* object, const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right)
        : Logic(LogicPriority::Highest), object(object), speed(speed), up(up), down(down), left(left), right(right)
{
}

void SGE::Logics::SimpleMove::performLogic()
{
	glm::vec2 move = {0,0};
	if (isPressed(this->up)) move.y += this->speed;
	if (isPressed(this->down)) move.y -= this->speed;
	if (isPressed(this->right)) move.x += this->speed;
	if (isPressed(this->left)) move.x -= this->speed;
	if (glm::vec2{ 0,0 }!=move)
	{
		move *= delta_time;
		this->sendAction(new SGE::ACTION::Move(this->object, move.x, move.y, 0));
	}
}
