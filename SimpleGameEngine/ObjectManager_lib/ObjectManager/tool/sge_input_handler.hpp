//
//  sge_input_handler.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 11/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_input_handler_h
#define sge_input_handler_h

#include <unordered_map>

#include "sge_key.hpp"
#include "sge_action_bind.hpp"
#include "sge_action_handler.hpp"
#include "glm/glm.hpp"

namespace SGE {

    class ObjectManager;
    class InputManager;
    class MouseObject;
    class InputBinder;

	/**
     * \brief 
     */
    class InputHandler {
	    /**
         * \brief 
         */
        ObjectManager* manager = nullptr;
	    /**
         * \brief 
         */
        InputManager* input_manager = nullptr;
	    /**
         * \brief 
         */
        std::unordered_map <Key, ActionBind, KeyHashAlias<Key>> keyMap;

	    /**
         * \brief 
         * \param k 
         */
        void pressKey(Key k);

    public:
	    /**
         * \brief 
         */
        InputHandler(ObjectManager *) noexcept;

	    /**
         * \brief 
         */
        void operator()(void) noexcept;

	    /**
         * \brief 
         * \param bind 
         */
        void mapAction(const InputBinder& bind);

	    /**
         * \brief 
         * \param bind 
         */
        void unmapAction(const InputBinder& bind);

	    /**
         * \brief 
         * \todo Move it?
         */
        class MouseHandler {
	        /**
             * \brief 
             */
            MouseObject* mouse = nullptr;

        public:
	        /**
             * \brief 
             */
            MouseHandler(void) noexcept;

	        /**
             * \brief 
             * \param coords 
             */
            void setMouseCoords(glm::vec2 coords) noexcept;

	        /**
             * \brief 
             * \return 
             */
            glm::vec2 getMouseCoords(void) const noexcept;

	        /**
             * \brief 
             * \return 
             */
            MouseObject *getMouseObject(void) noexcept;
        };

    private:
	    /**
         * \brief 
         */
        MouseHandler *mouseHandler = nullptr;
    public:
	    /**
         * \brief 
         * \return 
         */
        MouseHandler *getMouseHandler() noexcept;
    };

}

#endif /* sge_input_handler_h */
