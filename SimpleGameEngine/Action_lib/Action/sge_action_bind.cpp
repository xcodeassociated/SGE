//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_action_bind.hpp"

SGE::ActionBind::ActionBind(const std::initializer_list<ObjectID>& object, ActionID action): bind(object), aid(action)
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
