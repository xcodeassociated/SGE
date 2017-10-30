//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_input_binder.hpp"

SGE::InputBinder::InputBinder(std::initializer_list<ObjectID> object, ActionID action, Key key): kid(key)
{
    this->bind = ActionBind(object, action);
}

SGE::InputBinder::InputBinder(ObjectID object, ActionID action, Key key): kid(key)
{
    this->bind = ActionBind(object, action);
}

SGE::ActionBind SGE::InputBinder::getBind() const
{
    return this->bind;
}

SGE::Key SGE::InputBinder::getKey() const
{
    return this->kid;
}