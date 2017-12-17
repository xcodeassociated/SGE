//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_input_binder.hpp"

SGE::InputBinder::InputBinder(Action* action, Key key): bind(object, action), kid(key)
{
}

SGE::ActionBind SGE::InputBinder::getBind() const
{
    return this->bind;
}

SGE::Key SGE::InputBinder::getKey() const
{
    return this->kid;
}