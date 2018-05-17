#include "sge_logic.hpp"
#include "../Game/ActionHandler/sge_action_handler.hpp"

SGE::Logic::~Logic() {}


SGE::ActionHandler* SGE::Logic::action_handler = nullptr;

SGE::Logic::Logic(Priority _p): priority(_p)
{
}

void SGE::Logic::sendAction(Action* action) const
{
	action_handler->performSingleAction(action, this->priority);
}

SGE::Logic::Priority SGE::Logic::getPriority() const
{
	return this->priority;
}

void SGE::Logic::setOn(bool e)
{
	this->isOn = e;
}

bool SGE::Logic::getOn()
{
	return this->isOn;
}

void SGE::Logic::toggleOn()
{
	this->isOn = !this->isOn;
}
