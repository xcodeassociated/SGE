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

SGE::LogicBind::LogicBind(Logic::ID logic, Object::ID object): logic(logic), bind(object)
{
}

SGE::LogicID SGE::LogicBind::getLogic()
{
	return this->logic;
}

SGE::ObjectBind& SGE::LogicBind::getObject()
{
	return this->bind;
}

bool SGE::LogicBind::operator==(const LogicBind& b) const
{
	return logic == b.logic && bind[0] == b.bind[0];
}

bool SGE::LogicBind::operator<(const LogicBind& other) const
{
	if (bind[0].getID() == other.bind[0].getID())
	{
		return this->logic->getPriority() < other.logic->getPriority();
	}
	return bind[0].getID() < other.bind[0].getID();
}

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
