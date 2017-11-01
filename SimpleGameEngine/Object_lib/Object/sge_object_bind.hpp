//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_OBJECT_BIND_HPP
#define SGE_ZOMBIEGAME_SGE_OBJECT_BIND_HPP

#include <initializer_list>
#include <string>

namespace SGE {

    class ObjectID;

	/**
     * \brief 
     */
    class ObjectBind {
	    /**
         * \brief 
         */
        ObjectID* _begin = nullptr;
	    /**
         * \brief 
         */
        ObjectID* _end = nullptr;
    public:
	    /**
         * \brief 
         * \param object 
         */
        ObjectBind(const std::initializer_list<ObjectID>& object);
	    /**
         * \brief 
         * \param object 
         */
        ObjectBind(ObjectID object);
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
        ObjectID& operator[](std::size_t i);
	    /**
         * \brief 
         * \param i 
         * \return 
         */
        const ObjectID& operator[](std::size_t i) const;
	    /**
         * \brief 
         * \return 
         */
        ObjectID* begin();
	    /**
         * \brief 
         * \return 
         */
        ObjectID* end();
	    /**
         * \brief 
         * \return 
         */
        ObjectID* begin() const;
	    /**
         * \brief 
         * \return 
         */
        ObjectID* end() const;
	    /**
         * \brief 
         * \return 
         */
        std::size_t size() const;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_OBJECT_BIND_HPP
