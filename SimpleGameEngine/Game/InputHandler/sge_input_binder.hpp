//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP
#define SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP

#include "../../IO/Key/sge_key.hpp"

namespace SGE
{
    class Action;

	/**
     * \brief Binds Key with Action
     */
    class InputBinder
    {
	    /**
         * \brief Action pointer
         */
        Action* action = nullptr;
	    /**
         * \brief bound Key
         */
        Key key;

    public:

		/**
		 * \brief Constructs Input binder
		 * \param object List of objects to bind
		 * \param action Action ID to bind
		 * \param key Key to bind
		 */
        InputBinder(Action* action, Key key);

	    /**
         * \brief Returns bound Action pointer
         * \return bound Action pointer
         */
        Action* getAction() const;

	    /**
         * \brief Returns bound Key
         * \return bound Key
         */
        Key getKey() const;
    };

}


#endif //SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP
