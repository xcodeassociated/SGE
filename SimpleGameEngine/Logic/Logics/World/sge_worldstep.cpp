#include "../../../Utils/Timing/sge_fps_limiter.hpp"
#include "sge_worldstep.hpp"

SGE::WorldStep::WorldStep(b2World* w) noexcept : Logic(LogicPriority::Highest), world(w)
{
}

SGE::WorldStep::WorldStep(b2World* w, int v, int p) noexcept
	: Logic(LogicPriority::Highest), world(w), vel(v), pos(p)
{
}

void SGE::WorldStep::performLogic()
{
	this->world->Step(delta_time, this->vel, this->pos);
}

int SGE::WorldStep::getVelocityIterations() const
{
	return this->vel;
}

int SGE::WorldStep::getPositionIterations() const
{
	return this->pos;
}

void SGE::WorldStep::setVelocityIterations(int iter)
{
	this->vel = iter;
}

void SGE::WorldStep::setPositionIterations(int iter)
{
	this->pos = iter;
}
