#include "sge_logic_move.hpp"
#include "../../../Action/Actions/sge_action_move.hpp"
#include "../../../IO/KeyboardState/sge_keyboard_state.hpp"
#include "../../../Utils/Timing/sge_fps_limiter.hpp"
#include <glm/glm.hpp>
#include <glm/detail/type_vec2.hpp>

SGE::Logics::SimpleMove::SimpleMove(Object* object, const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right)
        : Logic(LogicPriority::Highest), object(object), speed(speed), up(up), down(down), left(left), right(right)
{
}

void SGE::Logics::SimpleMove::performLogic()
{
	glm::vec2 moveVec = {0,0};
	if (isPressed(this->up)) moveVec.y += this->speed;
	if (isPressed(this->down)) moveVec.y -= this->speed;
	if (isPressed(this->right)) moveVec.x += this->speed;
	if (isPressed(this->left)) moveVec.x -= this->speed;
	if (glm::vec2{ 0,0 } != moveVec)
	{
		moveVec *= delta_time;
		this->sendAction(new SGE::ACTION::Move(this->object, moveVec.x, moveVec.y, 0));
	}
}
