//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_ACTION_ID_HPP
#define SGE_ZOMBIEGAME_SGE_ACTION_ID_HPP

#include "sge_id.hpp"

namespace SGE {

    class Action;

	/**
     * \brief ID for Actions.
     */
    class ActionID : public ID {
        friend class ActionHandler;

        friend class ObjectManager;

	    /**
         * \brief Pointer to Action
         */
        Action *action = nullptr;

	    /**
         * \brief Constructs ActionID
         * \param id Assigned ID number
         * \param a Pointer to Action
         */
        ActionID(long id, Action *a);

    public:
	    /**
         * \brief Constructs ActionID with default ID number
         * \param a Pointer to Action
         */
        ActionID(Action *a);

	    /**
         * \brief Returns pointer to Action
         * \return Pointer to Action
         */
        Action *getAction() const;

	    /**
         * \brief Returns pointer to Action
         * \return Pointer to Action
         */
        Action *operator->() const;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_ACTION_ID_HPP
