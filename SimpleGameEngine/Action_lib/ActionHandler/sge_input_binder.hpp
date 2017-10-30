//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP
#define SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP

#include "sge_key.hpp"
#include "sge_action_bind.hpp"
#include "sge_action_id.hpp"

namespace SGE {

    class InputBinder{
        ActionBind bind;
        Key kid;

    public:
        InputBinder(std::initializer_list<ObjectID> object, ActionID action, Key key);

        InputBinder(ObjectID object, ActionID action, Key key);

        ActionBind getBind() const;

        Key getKey() const;
    };

}


#endif //SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP
