//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_OBJECT_BIND_HPP
#define SGE_ZOMBIEGAME_SGE_OBJECT_BIND_HPP

#include <initializer_list>
#include <string>

namespace SGE {

    class ObjectID;

    class ObjectBind {
        ObjectID* _begin = nullptr;
        ObjectID* _end = nullptr;
    public:
        ObjectBind(const std::initializer_list<ObjectID>& object);
        ObjectBind(ObjectID object);
        ObjectBind() = default;
        ~ObjectBind();
        ObjectBind(const ObjectBind& b);
        ObjectBind(ObjectBind&& b);

        ObjectBind& operator=(const ObjectBind& b);
        ObjectBind& operator=(ObjectBind&& b) noexcept;

        ObjectID& operator[](std::size_t i);
        const ObjectID& operator[](std::size_t i) const;
        ObjectID* begin();
        ObjectID* end();
        ObjectID* begin() const;
        ObjectID* end() const;
        std::size_t size() const;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_OBJECT_BIND_HPP
