#include "sge_logic_collide_basic.hpp"

SGE::Logics::BasicCollider::BasicCollider(Object::ID obj, collisionFunc _onCollision): Collide(_onCollision), obj(obj)
{
}

void SGE::Logics::BasicCollider::performLogic(const ObjectBind& _obj)
{
	Object* self = this->obj.getObject();
	Object* oponent = _obj[0].getObject();

	Shape* selfShape = self->getShape();
	Shape* oponentShape = oponent->getShape();

	bool collision = false;

	if (selfShape->getType() == oponentShape->getType())
		collision = this->collideWithSameShape(self, oponent);
	else
		collision = this->collideWithDifferentShape(self, oponent);

	if (collision)
	{
		ActionID aid = this->onCollision(obj, _obj[0]);
		this->sendAction(_obj[0], aid);
		//action_handler->performSingleAction(std::make_pair(_obj, aid), (this->priority == LogicPriority::Highest) );
	}
}
