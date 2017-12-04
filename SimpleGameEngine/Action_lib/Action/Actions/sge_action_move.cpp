#include "sge_action_move.hpp"
#include "sge_object_bind.hpp"

SGE::ACTION::Move::Move(float _x, float _y, double _duration): Action(_duration), destX(_x), destY(_y)
{
	;
}

void SGE::ACTION::Move::action_begin(const ObjectBind&) noexcept
{
	;
}

void SGE::ACTION::Move::action_main(const ObjectBind& bind) noexcept
{
	glm::vec2 pos = {0,0};
	for (Object* id : bind)
	{
		pos = id->getPosition();
		id->setPosition(pos.x + this->destX, pos.y + this->destY);
	}
}

void SGE::ACTION::Move::action_ends(const ObjectBind&) noexcept
{
	;
}
