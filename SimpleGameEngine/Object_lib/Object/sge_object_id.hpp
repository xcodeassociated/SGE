//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_OBJECT_ID_HPP
#define SGE_ZOMBIEGAME_SGE_OBJECT_ID_HPP

#include "sge_id.hpp"

namespace SGE {

    class Object;

    class ObjectID : public ID {
        friend class ObjectManager;
        friend class Renderer;

        Object* obj = nullptr;
        ObjectID(const long id, Object* o);
    public:
        ObjectID();
        ObjectID(Object* o);

        Object* getObject() const;

        Object* operator->() const;

        ObjectID(const ObjectID&) = default;
        ObjectID& operator=(const ObjectID&) = default;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_OBJECT_ID_HPP
