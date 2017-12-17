#include "sge_action_move.hpp"

SGE::ACTION::Move::Move(float _x, float _y, bool active): Action(active), destX(_x), destY(_y)
{
}

void SGE::ACTION::Move::action_begin(const ObjectBind&) noexcept
{
}

void SGE::ACTION::Move::action_main(const ObjectBind& bind) noexcept
{
	glm::vec2 pos = {0,0};
	for (Object* id : bind)
	{
		pos = id->getPosition();
		id->setPosition(pos.x + this->destX, pos.y + this->destY);
	}
	this->active = false;
}

void SGE::ACTION::Move::action_ends(const ObjectBind&) noexcept
{
}
