//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_ACTION_BIND_HPP
#define SGE_ZOMBIEGAME_SGE_ACTION_BIND_HPP


#include "sge_object_bind.hpp"
#include "sge_action_id.hpp"

namespace SGE {

    class Object;
    class ObjectID;
    class ActionHandler;
    class ObjectManager;

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
        ActionID aid = ActionID(nullptr);
    public:
	    /**
         * \brief Constructs ActionBind from list of Objects and ActionID
         * \param object Objects to be bound
         * \param action Action to be bound
         */
        ActionBind(const std::initializer_list<ObjectID>& object, ActionID action);

	    /**
         * \brief Constructs ActionBind from ObjectID and ActionID
         * \param object Object to be bound
         * \param action Action to be bound
         */
        ActionBind(ObjectID object, ActionID action);

	    /**
         * \brief Returns Iterator to first bound Object
         * \return Pointer to ObjectID
         */
        ObjectID* begin() const;

	    /**
         * \brief Returns Iterator past the last bound Object
         * \return Pointer to ObjectID
         */
        ObjectID* end() const;

	    /**
         * \brief Returns bound Action
         * \return Bound ActionID
         */
        const ActionID getAction() const;

	    /**
         * \brief Returns bound Objects
         * \return Bound ObjectBind
         */
        const ObjectBind& getBind() const;

	    /**
         * \brief Returns number of bound Objects
         * \return Bound ObjectBind size
         */
        std::size_t size() const;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_ACTION_BIND_HPP
