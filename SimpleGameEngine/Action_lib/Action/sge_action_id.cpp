//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_id.hpp"
#include "sge_action_id.hpp"

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