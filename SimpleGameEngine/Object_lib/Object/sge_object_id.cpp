//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_object_id.hpp"

SGE::ObjectID::ObjectID(const long id, SGE::Object* o) : ID(id), obj(o)
{
}

SGE::ObjectID::ObjectID() : ID(0)
{
}

SGE::ObjectID::ObjectID(SGE::Object* o) : ID(-1L), obj(o)
{
}

SGE::Object* SGE::ObjectID::getObject() const
{
    return this->obj;
}

SGE::Object* SGE::ObjectID::operator->() const
{
    return this->obj;
}