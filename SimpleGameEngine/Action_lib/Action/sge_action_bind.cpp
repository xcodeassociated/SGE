//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_action_bind.hpp"
#include "sge_object.hpp"

SGE::ActionBind::ActionBind(const std::initializer_list<Object*>& object, Action* action): bind(object), aid(action)
{
}

SGE::ActionBind::ActionBind(Object* object, Action* action) : ActionBind({ object }, action)
{
}

SGE::Object** SGE::ActionBind::begin() const
{
    return this->bind.begin();
}

SGE::Object** SGE::ActionBind::end() const
{
    return this->bind.end();
}

const SGE::Action* SGE::ActionBind::getAction() const
{
    return this->aid;
}

const SGE::ObjectBind& SGE::ActionBind::getBind() const
{
    return this->bind;
}

SGE::Action* SGE::ActionBind::getAction() 
{
	return this->aid;
}

SGE::ObjectBind& SGE::ActionBind::getBind() 
{
	return this->bind;
}

std::size_t SGE::ActionBind::size() const
{
    return this->bind.size();
}
