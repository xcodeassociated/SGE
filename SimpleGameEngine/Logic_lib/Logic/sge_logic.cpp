#include "sge_logic.hpp"
#include <sge_action_handler.hpp>

SGE::LogicID::LogicID(const long id, Logic* logic) : ID(id), logic(logic)
{
}

SGE::LogicID::LogicID(Logic* logic) : ID(-1L), logic(logic)
{
}

SGE::Logic* SGE::LogicID::getLogic() const
{
	return logic;
}

SGE::Logic* SGE::LogicID::operator->() const
{
	return logic;
}

SGE::Logic::~Logic() {}

SGE::ActionHandler* SGE::Logic::action_handler = nullptr;

SGE::Logic::Logic(Priority _p): priority(_p)
{
}

void SGE::Logic::sendAction(Object::ID obj, Action::ID action) const
{
	action_handler->performSingleAction(ActionBind(obj, action), this->priority);
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
