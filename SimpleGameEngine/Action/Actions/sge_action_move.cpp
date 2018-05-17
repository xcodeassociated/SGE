#include <glm/detail/type_vec2.hpp>
#include <cassert>

#include "sge_action_move.hpp"
#include "../../Object/sge_object.hpp"

SGE::ACTION::Move::Move(Object* object, float _x, float _y, bool active) : Action(active), object(object), destX(_x), destY(_y)
{
}

void SGE::ACTION::Move::action_begin() noexcept
{
}

void SGE::ACTION::Move::action_main() noexcept
{
	assert(object);

	glm::vec2 pos = object->getPosition();
	object->setPosition(pos.x + this->destX, pos.y + this->destY);

	this->active = false;
}

void SGE::ACTION::Move::action_ends() noexcept
{
}
