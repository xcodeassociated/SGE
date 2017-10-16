#include "sge_logic_collide_group.hpp"

SGE::Logics::BasicColliderGroup::BasicColliderGroup(std::vector<ObjectID> objects, collisionFunc _onCollision): Collide(_onCollision), objs(objects)
{
}

void SGE::Logics::BasicColliderGroup::performLogic(ObjectID _obj)
{
	ObjectID current;
	Object* self = nullptr;
	Object* oponent = _obj.getObject();

	Shape* selfShape = nullptr;
	Shape* oponentShape = oponent->getShape();

	bool collision = false;

	for (unsigned int i = 0; i < this->objs.size(); ++i)
	{
		current = this->objs[i];
		self = current.getObject();
		selfShape = self->getShape();
		if (selfShape->getType() == oponentShape->getType())
			collision = this->collideWithSameShape(self, oponent);
		else
			collision = this->collideWithDifferentShape(self, oponent);

		if (collision)
		{
			ActionID aid = this->onCollision(current, _obj);
			sendAction(current, aid);
		}
	}
}
