//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_ACTION_ID_HPP
#define SGE_ZOMBIEGAME_SGE_ACTION_ID_HPP

#include "sge_id.hpp"

namespace SGE {

    class Action;

    class ActionID : public ID {
        friend class ActionHandler;

        friend class ObjectManager;

        Action *action = nullptr;

        ActionID(long id, Action *a);

    public:
        ActionID(Action *a);

        Action *getAction() const;

        Action *operator->() const;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_ACTION_ID_HPP
