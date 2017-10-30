#include "sge_logic_collide.hpp"
#include "sge_action_move.hpp"
#include "sge_shape_rectangle.hpp"
#include "sge_shape_circle.hpp"
#include <glm/geometric.hpp>

SGE::ActionID SGE::Logics::Collide::RectangleCollisionVec(Object::ID still, Object::ID toMove)
{
	float vx = toMove.getObject()->getX() - still.getObject()->getX();
	float vy = toMove.getObject()->getY() - still.getObject()->getY();
	float penx = (reinterpret_cast<Rectangle*>(toMove.getObject()->getShape())->getWidth() + reinterpret_cast<Rectangle*>(still.getObject()->getShape())->getWidth()) * 0.5f - std::abs(vx);
	float peny = (reinterpret_cast<Rectangle*>(toMove.getObject()->getShape())->getHeight() + reinterpret_cast<Rectangle*>(still.getObject()->getShape())->getHeight()) * 0.5f - std::abs(vy);
	if (penx < peny)
		return ActionID(new ACTION::Move((vx > 0 ? penx : -penx), 0, 0));
	else
		return ActionID(new ACTION::Move(0, (vy > 0 ? peny : -peny), 0));
}

SGE::ActionID SGE::Logics::Collide::CircleCollisionVec(Object::ID still, Object::ID toMove)
{
	glm::vec2 pen = toMove.getObject()->getPosition() - still.getObject()->getPosition();
	float dist = reinterpret_cast<Circle*>(toMove.getObject()->getShape())->getRadius() + reinterpret_cast<Circle*>(still.getObject()->getShape())->getRadius();
	float l = glm::length(pen);
	pen *= ((dist - l) / l);
	return ActionID(new ACTION::Move(pen.x, pen.y, 0));
}

SGE::ActionID SGE::Logics::Collide::CircleToRectCollisionVec(Object::ID still, Object::ID toMove)
{
	glm::vec2 halfs(reinterpret_cast<Rectangle*>(still.getObject()->getShape())->getWidth() * .5f, reinterpret_cast<Rectangle*>(still.getObject()->getShape())->getHeight() * .5f);
	glm::vec2 difference = toMove.getObject()->getPosition() - still.getObject()->getPosition();
	glm::vec2 clamps = glm::clamp(difference, -halfs, halfs);
	halfs = still.getObject()->getPosition() + clamps;
	difference = toMove.getObject()->getPosition() - halfs;
	const float l = glm::length(difference);
	difference *= ((reinterpret_cast<Circle*>(toMove.getObject()->getShape())->getRadius() - l) / l);
	return ActionID(new ACTION::Move(difference.x, difference.y, 0));
}

bool SGE::Logics::Collide::collideWithSameShape(Object* self, Object* oponent)
{
	ShapeType commonShape = self->getShape()->getType();

	switch (commonShape)
	{
	case ShapeType::Circle:
		{
			Circle* selfCircle = reinterpret_cast<Circle*>(self->getShape());
			Circle* oponCircle = reinterpret_cast<Circle*>(oponent->getShape());
			glm::vec2 selfPos = self->getPosition();
			glm::vec2 oponPos = oponent->getPosition();
			if (glm::length(selfPos - oponPos) < (selfCircle->getRadius() + oponCircle->getRadius()))
			{
				return true;
			}
		}
		break;

	case ShapeType::Rectangle:
		{
			Rectangle* selfRect = reinterpret_cast<Rectangle*>(self->getShape());
			Rectangle* oponRect = reinterpret_cast<Rectangle*>(oponent->getShape());
			return (std::abs(self->getX() - oponent->getX()) * 2 < selfRect->getWidth() + oponRect->getWidth()
				&& std::abs(self->getY() - oponent->getY()) * 2 < selfRect->getHeight() + oponRect->getHeight());
		}
		break;

	case ShapeType::None:
		{
		}
	}

	return false;;
}

bool SGE::Logics::Collide::collideWithDifferentShape(Object* self, Object* oponent)
{
	ShapeType selfShapeType = self->getShape()->getType();
	ShapeType oponentShapeType = oponent->getShape()->getType();

	if (selfShapeType == ShapeType::None || oponentShapeType == ShapeType::None)
		return false;
	Circle* circle = nullptr;
	glm::vec2 circlePos;
	Rectangle* rect = nullptr;
	glm::vec2 rectPos;

	if ((selfShapeType == ShapeType::Circle && oponentShapeType == ShapeType::Rectangle) || (selfShapeType == ShapeType::Rectangle && oponentShapeType == ShapeType::Circle))
	{
		//Set up data for collision;
		if (selfShapeType == ShapeType::Circle)
		{
			circle = reinterpret_cast<Circle*>(self->getShape());
			rect = reinterpret_cast<Rectangle*>(oponent->getShape());
			circlePos = self->getPosition();
			rectPos = oponent->getPosition();
		}
		else
		{
			circle = reinterpret_cast<Circle*>(oponent->getShape());
			rect = reinterpret_cast<Rectangle*>(self->getShape());
			circlePos = oponent->getPosition();
			rectPos = self->getPosition();
		}
		//Quick AABB-AABB test;
		if (std::abs(circlePos.x - rectPos.x) < circle->getRadius() + rect->getWidth() * .5f
			&& std::abs(circlePos.y - rectPos.y) < circle->getRadius() + rect->getHeight() * .5f)
		{
			glm::vec2 halfs(rect->getWidth() * .5f, rect->getHeight() * .5f);
			glm::vec2 difference = circlePos - rectPos;
			glm::vec2 clamps = glm::clamp(difference, -halfs, halfs);
			halfs = rectPos + clamps;
			difference = circlePos - halfs;
			return glm::length(difference) < circle->getRadius();
		}
	}
	return false;
}

bool SGE::Logics::Collide::collideWithEdgesDifferentShape(Object* self, Object* oponent)
{
	ShapeType selfShapeType = self->getShape()->getType();
	ShapeType oponentShapeType = oponent->getShape()->getType();

	if (selfShapeType == ShapeType::None || oponentShapeType == ShapeType::None)
		return false;
	Circle* circle = nullptr;
	glm::vec2 circlePos;
	Rectangle* rect = nullptr;
	glm::vec2 rectPos;

	if ((selfShapeType == ShapeType::Circle && oponentShapeType == ShapeType::Rectangle) || (selfShapeType == ShapeType::Rectangle && oponentShapeType == ShapeType::Circle))
	{
		//Set up data for collision;
		if (selfShapeType == ShapeType::Circle)
		{
			circle = reinterpret_cast<Circle*>(self->getShape());
			rect = reinterpret_cast<Rectangle*>(oponent->getShape());
			circlePos = self->getPosition();
			rectPos = oponent->getPosition();
		}
		else
		{
			circle = reinterpret_cast<Circle*>(oponent->getShape());
			rect = reinterpret_cast<Rectangle*>(self->getShape());
			circlePos = oponent->getPosition();
			rectPos = self->getPosition();
		}
		//Quick AABB-AABB test;
		if (std::abs(circlePos.x - rectPos.x) <= circle->getRadius() + rect->getWidth() * .5f
			&& std::abs(circlePos.y - rectPos.y) <= circle->getRadius() + rect->getHeight() * .5f)
		{
			glm::vec2 halfs(rect->getWidth() * .5f, rect->getHeight() * .5f);
			glm::vec2 difference = circlePos - rectPos;
			glm::vec2 clamps = glm::clamp(difference, -halfs, halfs);
			halfs = rectPos + clamps;
			difference = halfs - circlePos;
			return glm::length(difference) <= circle->getRadius();
		}
	}
	return false;
}
