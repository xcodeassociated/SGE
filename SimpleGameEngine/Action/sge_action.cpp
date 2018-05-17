#include "sge_action.hpp"


SGE::Action::Action(bool active) : active(active)
{
}

bool SGE::Action::isActive() const
{
	return this->active;
}
