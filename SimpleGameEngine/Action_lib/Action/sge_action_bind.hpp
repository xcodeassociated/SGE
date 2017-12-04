//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_ACTION_BIND_HPP
#define SGE_ZOMBIEGAME_SGE_ACTION_BIND_HPP


#include "sge_object_bind.hpp"
namespace SGE {

    class Object;
    class ActionHandler;
    class ObjectManager;
	class Action;

	/**
     * \brief Binds Action with Objects
     */
    class ActionBind {
	    /**
         * \brief Bound Objects
         */
        ObjectBind bind = ObjectBind();
	    /**
         * \brief Bound Actions
         */
		Action* aid = nullptr;
    public:
	    /**
         * \brief Constructs ActionBind from list of Objects and ActionID
         * \param object Objects to be bound
         * \param action Action to be bound
         */
        ActionBind(const std::initializer_list<Object*>& object, Action* action);

	    /**
         * \brief Constructs ActionBind from Object and ActionID
         * \param object Object to be bound
         * \param action Action to be bound
         */
        ActionBind(Object* object, Action* action);

	    /**
         * \brief Returns Iterator to first bound Object
         * \return Pointer to Object
         */
        Object** begin() const;

	    /**
         * \brief Returns Iterator past the last bound Object
         * \return Pointer to Object
         */
        Object** end() const;

	    /**
         * \brief Returns bound Action
         * \return Bound ActionID
         */
        const Action* getAction() const;

	    /**
         * \brief Returns bound Objects
         * \return Bound ObjectBind
         */
        const ObjectBind& getBind() const;


		Action* getAction();

		/**
		* \brief Returns bound Objects
		* \return Bound ObjectBind
		*/
		ObjectBind& getBind();

	    /**
         * \brief Returns number of bound Objects
         * \return Bound ObjectBind size
         */
        std::size_t size() const;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_ACTION_BIND_HPP
