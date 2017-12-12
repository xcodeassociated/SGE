#include "sge_logic_collide_basic.hpp"
#include "sge_shape.hpp"
#include "sge_object.hpp"
#include "sge_object_bind.hpp"

SGE::Logics::BasicCollider::BasicCollider(Object* obj, const collisionFunc& _onCollision)
		: Collide(LogicPriority::Highest), onCollision(_onCollision), obj(obj)
{
}

void SGE::Logics::BasicCollider::performLogic(const ObjectBind& _obj)
{
	Object* self = this->obj;
	Object* oponent = _obj[0];

	Shape* selfShape = self->getShape();
	Shape* oponentShape = oponent->getShape();

	bool collision = false;

	if (selfShape->getType() == oponentShape->getType())
		collision = this->collideWithSameShape(self, oponent);
	else
		collision = this->collideWithDifferentShape(self, oponent);

	if (collision)
	{
		Action* aid = this->onCollision(obj, _obj[0]);
		this->sendAction(_obj[0], aid);
	}
}
