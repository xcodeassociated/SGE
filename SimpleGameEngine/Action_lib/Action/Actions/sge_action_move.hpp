//
//  sge_action_move.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 06/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_action_move_h
#define sge_action_move_h

#include "sge_action.hpp"

namespace SGE
{
    namespace ACTION
	{
	    /**
         * \brief Immediately moves bound objects by given distance
         * \todo Make use of duration or remove it
         */
        class Move : virtual public Action
		{
	        /**
	         * \brief Displacement distance on X axis
	         */
	        float destX;
	        /**
	         * \brief Displacement distance on Y axis
	         */
	        float destY;

        public:

	        /**
	         * \brief Construct Move
	         * \param _x destX value
	         * \param _y destY value
	         * \param active
	         */
	        Move(float _x, float _y, bool active);

        private:

	        /**
	         * \brief Unused
	         */
	        virtual void action_begin(const ObjectBind&) noexcept override;

	        /**
	         * \brief Moves each object by given distance
	         * \param bind Objects to execute
	         */
	        virtual void action_main(const ObjectBind& bind) noexcept override;

	        /**
	         * \brief Unused
	         */
	        virtual void action_ends(const ObjectBind&) noexcept override;
        };
    }
}

#endif /* sge_action_move_h */
