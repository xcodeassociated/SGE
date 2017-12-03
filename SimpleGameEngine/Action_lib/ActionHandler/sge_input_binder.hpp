//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP
#define SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP

#include "sge_key.hpp"
#include "sge_action_bind.hpp"

namespace SGE {

	/**
     * \brief Binds Key with ActionBind
     */
    class InputBinder{
	    /**
         * \brief bound ActionBind
         */
        ActionBind bind;
	    /**
         * \brief bound Key
         */
        Key kid;

    public:
	    /**
         * \brief Constructs Input binder
         * \param object List of objects to bind
         * \param action Action ID to bind
         * \param key Key to bind
         */
        InputBinder(std::initializer_list<Object*> object, Action* action, Key key);

		/**
		 * \brief Constructs Input binder
		 * \param object List of objects to bind
		 * \param action Action ID to bind
		 * \param key Key to bind
		 */
        InputBinder(Object* object, Action* action, Key key);

	    /**
         * \brief Returns bound ActionBind
         * \return bound ActionBind
         */
        ActionBind getBind() const;

	    /**
         * \brief Returns bound Key
         * \return bound Key
         */
        Key getKey() const;
    };

}


#endif //SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP
