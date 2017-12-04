#include "sge_logic_move.hpp"
#include <sge_action_move.hpp>
#include <sge_keyboard_state.hpp>
#include "sge_object_bind.hpp"

SGE::Logics::SimpleMove::SimpleMove(const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right): Logic(LogicPriority::Highest), speed(speed), up(up), down(down), left(left), right(right)
{
}

void SGE::Logics::SimpleMove::performLogic(const ObjectBind& obj)
{
	glm::vec2 move = {0,0};
	if (isPressed(this->up)) move.y += this->speed;
	if (isPressed(this->down)) move.y -= this->speed;
	if (isPressed(this->right)) move.x += this->speed;
	if (isPressed(this->left)) move.x -= this->speed;
	if (glm::vec2{ 0,0 }!=move)
		this->sendAction(obj[0], new SGE::ACTION::Move(move.x, move.y, 0));
}
