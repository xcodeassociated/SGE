//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_object_bind.hpp"
#include "sge_object.hpp"

SGE::ObjectBind::ObjectBind(const std::initializer_list<Object*>& object)
{
    this->_begin = new Object*[object.size()];
    int i = 0;
    for (Object* o : object) {
        *(this->_begin + i) = o;
        i++;
    }
    this->_end = (this->_begin + object.size());
}

SGE::ObjectBind::ObjectBind(Object* object) : ObjectBind({ object })
{
}

SGE::ObjectBind::~ObjectBind()
{
    if (this->_begin != nullptr)
        delete[] this->_begin;
}

SGE::ObjectBind::ObjectBind(const ObjectBind& b)
{
	Object** begin = b._begin;
	Object** end = b._end;

    this->_begin = new Object*[b.size()];
    int i = 0;
	for (auto* it = begin; it != end; ++it) {
        this->_begin[i] = *it;
        i++;
    }
    this->_end = (this->_begin + i);
}

SGE::ObjectBind::ObjectBind(ObjectBind&& b) noexcept : _begin(b._begin), _end(b._end)
{
    b._begin = nullptr;
    b._end = nullptr;
}

SGE::ObjectBind& SGE::ObjectBind::operator=(const ObjectBind& b)
{
    if (this != &b) {
		Object** begin = b._begin;
		Object** end = b._end;

        this->_begin = new Object*[b.size()];
        int i = 0;
        for (auto* it = begin; it != end; ++it) {
            *(this->_begin + i) = *it;
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

SGE::Object*& SGE::ObjectBind::operator[](std::size_t i)
{
    return *(this->_begin + i);
}

SGE::Object*const& SGE::ObjectBind::operator[](std::size_t i) const
{
    return *(this->_begin + i);
}

SGE::Object** SGE::ObjectBind::begin()
{
    return this->_begin;
}

SGE::Object** SGE::ObjectBind::end()
{
    return this->_end;
}

SGE::Object** SGE::ObjectBind::begin() const
{
    return this->_begin;
}

SGE::Object** SGE::ObjectBind::end() const
{
    return this->_end;
}

std::size_t SGE::ObjectBind::size() const
{
    return this->_end - this->_begin;
}