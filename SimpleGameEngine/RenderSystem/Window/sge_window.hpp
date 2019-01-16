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

struct SDL_Window;

namespace SGE
{

    class Window
    {
        SDL_Window* window = nullptr;
	    int width = 0;
	    int height = 0;

    public:
        Window(std::pair<int, int>) noexcept;

        void createWindow();
        void showWindow() noexcept;
        void finalizeWindow() noexcept;
        SDL_Window* getWindow() noexcept;
	    bool isHidden() const;
    };

}

#endif /* sge_window_h */
