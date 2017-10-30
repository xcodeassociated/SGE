//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_object_bind.hpp"
#include "sge_object_id.hpp"

SGE::ObjectBind::ObjectBind(const std::initializer_list<ObjectID>& object)
{
    this->_begin = new ObjectID[object.size()];
    int i = 0;
    for (ObjectID o : object) {
        *(this->_begin + i) = o;
        i++;
    }
    this->_end = (this->_begin + object.size());
}

SGE::ObjectBind::ObjectBind(ObjectID object) : ObjectBind({ object })
{
}

SGE::ObjectBind::~ObjectBind()
{
    if (this->_begin != nullptr)
        delete[] this->_begin;
}

SGE::ObjectBind::ObjectBind(const ObjectBind& b)
{
    this->_begin = new ObjectID[b.size()];
    int i = 0;
    for (ObjectID o : b) {
        *(this->_begin + i) = o;
        i++;
    }
    this->_end = (this->_begin + i);
}

SGE::ObjectBind::ObjectBind(ObjectBind&& b) : _begin(b._begin), _end(b._end)
{
    b._begin = nullptr;
    b._end = nullptr;
}

SGE::ObjectBind& SGE::ObjectBind::operator=(const ObjectBind& b)
{
    if (this != &b) {
        this->_begin = new ObjectID[b.size()];
        int i = 0;
        for (ObjectID o : b) {
            *(this->_begin + i) = o;
            i++;
        }
        this->_end = (this->_begin + i);
    }
    return *this;
}

SGE::ObjectBind& SGE::ObjectBind::operator=(ObjectBind&& b) noexcept
{
    if (this != &b) {
        this->_begin = b._begin;
        this->_end = b._end;
        b._begin = nullptr;
        b._end = nullptr;
    }
    return *this;
}

SGE::ObjectID& SGE::ObjectBind::operator[](std::size_t i)
{
    return *(this->_begin + i);
}

const SGE::ObjectID& SGE::ObjectBind::operator[](std::size_t i) const
{
    return *(this->_begin + i);
}

SGE::ObjectID* SGE::ObjectBind::begin()
{
    return this->_begin;
}

SGE::ObjectID* SGE::ObjectBind::end()
{
    return this->_end;
}

SGE::ObjectID* SGE::ObjectBind::begin() const
{
    return this->_begin;
}

SGE::ObjectID* SGE::ObjectBind::end() const
{
    return this->_end;
}

std::size_t SGE::ObjectBind::size() const
{
    return this->_end - this->_begin;
}