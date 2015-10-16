//
//  MainGameWindow.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 16.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef MainGameWindow_h
#define MainGameWindow_h

#include "../include/SGE_include.hpp"

namespace SGE {

    enum class GameState {PLAY, EXIT};
    
    class MainGameWindow{
    //private:
        SDL_Window* mainWindow = nullptr;
        GameState gameState;
        
        int mainWindowPosX = 0, mainWindowPosY = 0;
        int mainWindowWidth = 0, mainWindowHeight = 0;
        
        bool isInited = false;
        
    public:
        MainGameWindow(){
                std::cout << ">>    MainGameWindow constructed!" << std::endl;
        };
        
        ~MainGameWindow(){
            
            SDL_DestroyWindow(this->mainWindow);
            SDL_Quit();
            
                std::cout << ">>    MainGameWindow deconstructed!" << std::endl;
        };
        
        void init(){
            if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "error:    SDL_init";
       
            this->mainWindowPosX = SDL_WINDOWPOS_CENTERED;
            this->mainWindowPosY = SDL_WINDOWPOS_CENTERED;
            
            this->mainWindowWidth = 1024;
            this->mainWindowHeight = 768;
            
            this->gameState = GameState::PLAY;
            
            this->isInited = true;
            
                std::cout << ">>    GameEngine initialized." << std::endl;
        };
        
        void processInput(){
            SDL_Event event;
            while (SDL_PollEvent(&event)){
                switch (event.type) {
                    case SDL_QUIT:{
                        this->gameState = GameState::EXIT;
                            std::cout << ">>    Window Cloased!" << std::endl;
                    }break;
                        
                    case SDL_MOUSEMOTION:{
                        std::cout << " x: " << event.motion.x << " y: " << event.motion.y << std::endl;
                    }break;
                        
                    case SDL_MOUSEBUTTONDOWN:{
                        //...
                    }break;
                    
                    case SDL_MOUSEBUTTONUP:{
                        //...
                    }break;
                        
                    case SDL_KEYDOWN:{
                        //...
                    }break;
                        
                    case SDL_KEYUP:{
                        //...
                    }break;
                    
                    default:{}break;
                }
            };
            
        };

        /** Main Game loop **/
        void gameLoop(){
            
            while (this->gameState != GameState::EXIT){
                this->processInput();
                //...
                
                SDL_Delay(2);
            };
            
           //do something with the window...
            
                std::cout << ">>    GameLoop brake" << std::endl;
        }
        
        void show(){
            if (this->isInited){
                this->mainWindow = SDL_CreateWindow("SGE",
                                                    this->mainWindowPosX,
                                                    this->mainWindowPosY,
                                                    this->mainWindowWidth,
                                                    this->mainWindowHeight,
                                                    SDL_WINDOW_OPENGL);
                
                SDL_ShowWindow(this->mainWindow);
                
                if (this->mainWindow == NULL) throw "error: ";
            }else
                std::cout << ">>    init first!" << std::endl;
        };
        
    };
    
}

#endif /* MainGameWindow_h */
