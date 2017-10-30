//
//  sge_window.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 11/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_window_h
#define sge_window_h

#include <utility>

class SDL_Window;

namespace SGE {

    class ObjectManager;

    class WindowManager {
        ObjectManager* manager = nullptr;
        SDL_Window* window = nullptr;
        int width = 0, height = 0;

    public:
        WindowManager(std::pair<int, int>, ObjectManager*) noexcept;

        void createWindow(void);

        void showWindow(void) noexcept;

        void finalizeWindow(void) noexcept;

        SDL_Window* getWindow(void) noexcept;
    };

}

#endif /* sge_window_h */
