#include "sge_logic_collide.hpp"
#include "../../../Action/Actions/sge_action_move.hpp"
#include "../../../Object/Shape/sge_shape.hpp"
#include <glm/geometric.hpp>
#include "../../../Object/sge_object.hpp"

SGE::Action* SGE::Logics::Collide::RectangleCollisionVec(Object* still, Object* toMove)
{
	float vx = toMove->getXGLM() - still->getXGLM();
	float vy = toMove->getYGLM() - still->getYGLM();
	float penx = toMove->getShape()->getWidth() + still->getShape()->getWidth() * 0.5f - std::abs(vx);
	float peny = toMove->getShape()->getHeight() + still->getShape()->getHeight() * 0.5f - std::abs(vy);
	if (penx < peny)
		return new ACTION::Move(toMove, (vx > 0 ? penx : -penx), 0, true);
	else
		return new ACTION::Move(toMove, 0, (vy > 0 ? peny : -peny), true);
}

SGE::Action* SGE::Logics::Collide::CircleCollisionVec(Object* still, Object* toMove)
{
	glm::vec2 pen = toMove->getPositionGLM() - still->getPositionGLM();
	float dist = toMove->getShape()->getRadius() + still->getShape()->getRadius();
	float l = glm::length(pen);
	pen *= ((dist - l) / l);
	return new ACTION::Move(toMove, pen.x, pen.y, true);
}

SGE::Action* SGE::Logics::Collide::CircleToRectCollisionVec(Object* still, Object* toMove)
{
	glm::vec2 halfs(still->getShape()->getWidth() * .5f, still->getShape()->getHeight() * .5f);
	glm::vec2 difference = toMove->getPositionGLM() - still->getPositionGLM();
	glm::vec2 clamps = glm::clamp(difference, -halfs, halfs);
	halfs = still->getPositionGLM() + clamps;
	difference = toMove->getPositionGLM() - halfs;
	const float l = glm::length(difference);
	difference *= ((toMove->getShape()->getRadius() - l) / l);
	return new ACTION::Move(toMove, difference.x, difference.y, true);
}

bool SGE::Logics::Collide::collideWithSameShape(Object* self, Object* oponent)
{
	ShapeType commonShape = self->getShape()->getType();

	switch (commonShape)
	{
	case ShapeType::Circle:
		{
			Shape* selfCircle = self->getShape();
			Shape* oponCircle = oponent->getShape();
			glm::vec2 selfPos = self->getPositionGLM();
			glm::vec2 oponPos = oponent->getPositionGLM();
			if (glm::length(selfPos - oponPos) < (selfCircle->getRadius() + oponCircle->getRadius()))
			{
				return true;
			}
		}
		break;

	case ShapeType::Rectangle:
		{
			Shape* selfRect = self->getShape();
			Shape* oponRect = oponent->getShape();
			return (std::abs(self->getXGLM() - oponent->getXGLM()) * 2 < selfRect->getWidth() + oponRect->getWidth()
				&& std::abs(self->getYGLM() - oponent->getYGLM()) * 2 < selfRect->getHeight() + oponRect->getHeight());
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
	Shape* circle = nullptr;
	glm::vec2 circlePos;
	Shape* rect = nullptr;
	glm::vec2 rectPos;

	if ((selfShapeType == ShapeType::Circle && oponentShapeType == ShapeType::Rectangle) || (selfShapeType == ShapeType::Rectangle && oponentShapeType == ShapeType::Circle))
	{
		//Set up data for collision;
		if (selfShapeType == ShapeType::Circle)
		{
			circle = self->getShape();
			rect =oponent->getShape();
			circlePos = self->getPositionGLM();
			rectPos = oponent->getPositionGLM();
		}
		else
		{
			circle = oponent->getShape();
			rect = self->getShape();
			circlePos = oponent->getPositionGLM();
			rectPos = self->getPositionGLM();
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
	Shape* circle = nullptr;
	glm::vec2 circlePos;
	Shape* rect = nullptr;
	glm::vec2 rectPos;

	if ((selfShapeType == ShapeType::Circle && oponentShapeType == ShapeType::Rectangle) || (selfShapeType == ShapeType::Rectangle && oponentShapeType == ShapeType::Circle))
	{
		//Set up data for collision;
		if (selfShapeType == ShapeType::Circle)
		{
			circle = self->getShape();
			rect = oponent->getShape();
			circlePos = self->getPositionGLM();
			rectPos = oponent->getPositionGLM();
		}
		else
		{
			circle = oponent->getShape();
			rect = self->getShape();
			circlePos = oponent->getPositionGLM();
			rectPos = self->getPositionGLM();
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
