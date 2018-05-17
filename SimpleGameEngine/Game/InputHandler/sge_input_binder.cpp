//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_input_binder.hpp"

SGE::InputBinder::InputBinder(Action* action, Key key) : action(action), key(key)
{
}

SGE::Action* SGE::InputBinder::getAction() const
{
    return this->action;
}

SGE::Key SGE::InputBinder::getKey() const
{
    return this->key;
}