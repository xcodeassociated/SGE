#include "sge_logic_collide_basic.hpp"
#include "../../../Object/Shape/sge_shape.hpp"
#include "../../../Object/sge_object.hpp"

SGE::Logics::BasicCollider::BasicCollider(Object* object_a, Object* object_b, const collisionFunc& _onCollision)
		: Collide(LogicPriority::Highest), onCollision(_onCollision), object_a(object_a), object_b(object_b)
{
}

void SGE::Logics::BasicCollider::performLogic()
{
	Object* self = this->object_a;
	Object* oponent = this->object_b;

	Shape* selfShape = self->getShape();
	Shape* oponentShape = oponent->getShape();

	bool collision = false;

	if (selfShape->getType() == oponentShape->getType())
		collision = this->collideWithSameShape(self, oponent);
	else
		collision = this->collideWithDifferentShape(self, oponent);

	if (collision)
	{
		Action* aid = this->onCollision(self, oponent);
		this->sendAction(aid);
	}
}
