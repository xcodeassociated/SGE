#include "sge_logic_collide_group.hpp"
#include "../../../Object/Shape/sge_shape.hpp"
#include "../../../Object/sge_object.hpp"

SGE::Logics::BasicColliderGroup::BasicColliderGroup(Object* object, std::vector<Object*> objects, const collisionFunc& _onCollision)
		: Collide(LogicPriority::Highest), onCollision(_onCollision), object(object), objs(objects)
{
}

void SGE::Logics::BasicColliderGroup::performLogic()
{
	Object* current;
	Object* self = nullptr;
	Object* oponent = this->object;

	Shape* selfShape = nullptr;
	Shape* oponentShape = oponent->getShape();

	bool collision = false;

	for (unsigned int i = 0; i < this->objs.size(); ++i)
	{
		current = this->objs[i];
		self = current;
		selfShape = self->getShape();
		if (selfShape->getType() == oponentShape->getType())
			collision = this->collideWithSameShape(self, oponent);
		else
			collision = this->collideWithDifferentShape(self, oponent);

		if (collision)
		{
			Action* aid = this->onCollision(current, this->object);
			sendAction(aid);
		}
	}
}
