//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_ACTION_BIND_HPP
#define SGE_ZOMBIEGAME_SGE_ACTION_BIND_HPP


#include "sge_object.hpp" // need to be changed to sge_object_bind
#include "sge_action_id.hpp"

namespace SGE {

    class Object;
    class ObjectID;
    class ActionHandler;
    class ObjectManager;

    class ActionBind {
        ObjectBind bind = ObjectBind();
        ActionID aid = ActionID(nullptr);
    public:
        ActionBind(const std::initializer_list<ObjectID>& object, ActionID action);

        ActionBind(ObjectID object, ActionID action);
        ActionBind() = default;

        ObjectID* begin() const;

        ObjectID* end() const;

        ActionID getAction() const;

        const ObjectBind& getBind() const;

        std::size_t size() const;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_ACTION_BIND_HPP
