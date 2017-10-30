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

namespace SGE {

    class ObjectManager;
    class InputManager;
    class MouseObject;
    class InputBinder;

    class InputHandler {
        ObjectManager* manager = nullptr;
        InputManager* input_manager = nullptr;
        std::unordered_map <Key, ActionBind, KeyHashAlias<Key>> keyMap;

        void pressKey(Key k);

    public:
        InputHandler(ObjectManager *) noexcept;

        void operator()(void) noexcept;

        void mapAction(const InputBinder& bind);

        void unmapAction(const InputBinder& bind);

        class MouseHandler {
            MouseObject* mouse = nullptr;

        public:
            MouseHandler(void) noexcept;

            void setMouseCoords(glm::vec2 coords) noexcept;

            glm::vec2 getMouseCoords(void) const noexcept;

            MouseObject *getMouseObject(void) noexcept;
        };

    private:
        MouseHandler *mouseHandler = nullptr;
    public:
        MouseHandler *getMouseHandler() noexcept;
    };

}

#endif /* sge_input_handler_h */
