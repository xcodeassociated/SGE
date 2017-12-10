//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_OBJECT_BIND_HPP
#define SGE_ZOMBIEGAME_SGE_OBJECT_BIND_HPP

#include <initializer_list>
#include <string>

namespace SGE
{

    class Object;

	/**
     * \brief 
     */
    class ObjectBind
    {
	    /**
         * \brief 
         */
        Object** _begin = nullptr;
	    /**
         * \brief 
         */
        Object** _end = nullptr;
    public:
	    /**
         * \brief 
         * \param object 
         */
        ObjectBind(const std::initializer_list<Object*>& object);
	    /**
         * \brief 
         * \param object 
         */
        ObjectBind(Object* object);
	    /**
         * \brief 
         */
        ObjectBind() = default;
	    /**
         * \brief 
         */
        ~ObjectBind();
	    /**
         * \brief 
         * \param b 
         */
        ObjectBind(const ObjectBind& b);
	    /**
         * \brief 
         * \param b 
         */
        ObjectBind(ObjectBind&& b) noexcept;

	    /**
         * \brief 
         * \param b 
         * \return 
         */
        ObjectBind& operator=(const ObjectBind& b);
	    /**
         * \brief 
         * \param b 
         * \return 
         */
        ObjectBind& operator=(ObjectBind&& b) noexcept;

	    /**
         * \brief 
         * \param i 
         * \return 
         */
        Object*& operator[](std::size_t i);
	    /**
         * \brief 
         * \param i 
         * \return 
         */
        Object *const& operator[](std::size_t i) const;
	    /**
         * \brief 
         * \return 
         */
        Object** begin();
	    /**
         * \brief 
         * \return 
         */
        Object** end();
	    /**
         * \brief 
         * \return 
         */
        Object** begin() const;
	    /**
         * \brief 
         * \return 
         */
        Object** end() const;
	    /**
         * \brief 
         * \return 
         */
        std::size_t size() const;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_OBJECT_BIND_HPP
