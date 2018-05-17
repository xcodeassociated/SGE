#include "sge_logic_collide_level.hpp"
#include "../../../Object/Shape/sge_shape_rectangle.hpp"

SGE::Logics::BasicLevelCollider::BasicLevelCollider(Object* object, std::vector<WorldElement>& objects, const collisionFunc& _onCollision)
		: Collide(LogicPriority::Highest), onCollision(_onCollision), object(object), objs(objects)
{
}

void SGE::Logics::BasicLevelCollider::performLogic()
{
	Object* oponent = this->object;
	Shape* selfShape = getBaseTileShape();
	Shape* oponentShape = oponent->getShape();

	bool collision = false;

	for (unsigned int i = 0; i < this->objs.size(); ++i)
	{
		if (selfShape->getType() == oponentShape->getType())
			collision = this->collideWithSameShape(&objs[i], oponent);
		else
			collision = this->collideWithDifferentShape(&objs[i], oponent);

		if (collision)
		{
			Action* aid = this->onCollision(&objs[i], this->object);
			this->sendAction(aid);
		}
	}
}
