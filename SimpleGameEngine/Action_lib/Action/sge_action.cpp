#include "sge_action.hpp"

SGE::ActionID::ActionID(long id, Action* a):
	ID(id),
	action(a)
{
}

SGE::ActionID::ActionID(Action* a): ID(-1L), action(a)
{
}

SGE::Action* SGE::ActionID::getAction() const
{
	return this->action;
}

SGE::Action* SGE::ActionID::operator->() const
{
	return this->action;
}

SGE::Action::Action(double _d): duration(_d)
{
}

SGE::Action::Action(double _d, bool): duration(_d)
{
}

double SGE::Action::getDuration() const
{
	return this->duration;
}

SGE::ActionBind::ActionBind(const std::initializer_list<ObjectID>& object, Action::ID action): bind(object), aid(action)
{
}

SGE::ActionBind::ActionBind(ObjectID object, ActionID action) :ActionBind({ object }, action)
{
}

SGE::ObjectID* SGE::ActionBind::begin() const
{
	return this->bind.begin();
}

SGE::ObjectID* SGE::ActionBind::end() const
{
	return this->bind.end();
}

SGE::ActionID SGE::ActionBind::getAction() const
{
	return this->aid;
}

const SGE::ObjectBind& SGE::ActionBind::getBind() const
{
	return this->bind;
}

std::size_t SGE::ActionBind::size() const
{
	return this->bind.size();
}
