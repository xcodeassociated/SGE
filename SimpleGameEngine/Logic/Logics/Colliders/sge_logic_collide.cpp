#include "sge_logic_collide.hpp"
#include "../../../Action/Actions/sge_action_move.hpp"
#include "../../../Object/Shape/sge_shape_rectangle.hpp"
#include "../../../Object/Shape/sge_shape_circle.hpp"
#include <glm/geometric.hpp>
#include "../../../Object/sge_object.hpp"

SGE::Action* SGE::Logics::Collide::RectangleCollisionVec(Object* still, Object* toMove)
{
	float vx = toMove->getX() - still->getX();
	float vy = toMove->getY() - still->getY();
	float penx = (reinterpret_cast<Rectangle*>(toMove->getShape())->getWidth() + reinterpret_cast<Rectangle*>(still->getShape())->getWidth()) * 0.5f - std::abs(vx);
	float peny = (reinterpret_cast<Rectangle*>(toMove->getShape())->getHeight() + reinterpret_cast<Rectangle*>(still->getShape())->getHeight()) * 0.5f - std::abs(vy);
	if (penx < peny)
		return new ACTION::Move(toMove, (vx > 0 ? penx : -penx), 0, true);
	else
		return new ACTION::Move(toMove, 0, (vy > 0 ? peny : -peny), true);
}

SGE::Action* SGE::Logics::Collide::CircleCollisionVec(Object* still, Object* toMove)
{
	glm::vec2 pen = toMove->getPosition() - still->getPosition();
	float dist = reinterpret_cast<Circle*>(toMove->getShape())->getRadius() + reinterpret_cast<Circle*>(still->getShape())->getRadius();
	float l = glm::length(pen);
	pen *= ((dist - l) / l);
	return new ACTION::Move(toMove, pen.x, pen.y, true);
}

SGE::Action* SGE::Logics::Collide::CircleToRectCollisionVec(Object* still, Object* toMove)
{
	glm::vec2 halfs(reinterpret_cast<Rectangle*>(still->getShape())->getWidth() * .5f, reinterpret_cast<Rectangle*>(still->getShape())->getHeight() * .5f);
	glm::vec2 difference = toMove->getPosition() - still->getPosition();
	glm::vec2 clamps = glm::clamp(difference, -halfs, halfs);
	halfs = still->getPosition() + clamps;
	difference = toMove->getPosition() - halfs;
	const float l = glm::length(difference);
	difference *= ((reinterpret_cast<Circle*>(toMove->getShape())->getRadius() - l) / l);
	return new ACTION::Move(toMove, difference.x, difference.y, true);
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

SGE::Logics::Collide::Collide(const LogicPriority& logicPriority) : Logic(logicPriority)
{
}
