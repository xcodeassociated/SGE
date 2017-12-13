#include "sge_action.hpp"


SGE::Action::Action(double _d) : duration(_d)
{
}

double SGE::Action::getDuration() const
{
	return this->duration;
}
