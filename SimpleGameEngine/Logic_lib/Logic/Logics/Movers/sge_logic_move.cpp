#include "sge_logic_move.hpp"
#include <sge_action_move.hpp>
#include <sge_keyboard_state.hpp>

void SGE::Logics::SimpleMove::performLogic(const ObjectBind& obj)
{
	glm::vec2 move = {0,0};
	if (isPressed(this->up)) move.y += this->speed;
	if (isPressed(this->down)) move.y -= this->speed;
	if (isPressed(this->right)) move.x += this->speed;
	if (isPressed(this->left)) move.x -= this->speed;
	this->sendAction(obj[0], SGE::Action::ID(new SGE::ACTION::Move(move.x, move.y, 0)));
}
