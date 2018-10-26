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
	/**
     * \brief 
     */
    class WindowManager
    {
	    /**
         * \brief 
         */
        SDL_Window* window = nullptr;
	    /**
	     * \brief 
	     */
	    int width = 0;
	    /**
	     * \brief 
	     */
	    int height = 0;

    public:
	    /**
         * \brief 
         */
        WindowManager(std::pair<int, int>) noexcept;

	    /**
         * \brief 
         */
        void createWindow();

	    /**
         * \brief 
         */
        void showWindow() noexcept;
	    void hideWindow() noexcept;

	    /**
         * \brief 
         */
        void finalizeWindow() noexcept;

	    /**
         * \brief 
         * \return 
         */
        SDL_Window* getWindow() noexcept;
	    bool isHidden() const;
    };

}

#endif /* sge_window_h */
