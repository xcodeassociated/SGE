//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_OBJECT_ID_HPP
#define SGE_ZOMBIEGAME_SGE_OBJECT_ID_HPP

#include "sge_id.hpp"

namespace SGE {

    class Object;

	/**
     * \brief 
     */
    class ObjectID : public ID {
        friend class ObjectManager;
        friend class Renderer;

	    /**
         * \brief 
         */
        Object* obj = nullptr;
	    /**
         * \brief 
         * \param id 
         * \param o 
         */
        ObjectID(const long id, Object* o);
    public:
	    /**
         * \brief 
         */
        ObjectID();
	    /**
         * \brief 
         * \param o 
         */
        ObjectID(Object* o);

	    /**
         * \brief 
         * \return 
         */
        Object* getObject() const;

	    /**
         * \brief 
         * \return 
         */
        Object* operator->() const;

	    /**
         * \brief 
         */
        ObjectID(const ObjectID&) = default;
	    /**
         * \brief 
         * \return 
         */
        ObjectID& operator=(const ObjectID&) = default;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_OBJECT_ID_HPP
