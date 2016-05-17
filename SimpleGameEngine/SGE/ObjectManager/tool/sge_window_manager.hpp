//
//  sge_window.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 11/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_window_h
#define sge_window_h

namespace SGE {
	
	// multiple noexcepts in function that throw
    ObjectManager::WindowManager::WindowManager(std::pair<int, int> resolution, ObjectManager* m) noexcept : width(resolution.first), height(resolution.second) {
        this->manager = m;
    }
    
    void ObjectManager::WindowManager::createWindow(void){
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "error:    SDL_init";
        
        this->window = SDL_CreateWindow("SGE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_OPENGL);
        
        if (this->window == nullptr)
            throw "error: ";
        
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
        SDL_GLContext glContext = SDL_GL_CreateContext(this->window);
        if (glContext == nullptr) throw "";
        
        glewExperimental = GL_TRUE;
        GLenum glewCheck = glewInit();
        if (glewCheck != GLEW_OK) throw "";
        
        /* !!!! sene should be able to pick a background color !!!*/ glClearColor(.7f, .7f, .7f, 1.0f);
        
        SDL_GL_SetSwapInterval(1);
        
        const GLubyte* version = glGetString(GL_VERSION);
        const char* glVersionChar = reinterpret_cast< const char* >(version);
        
        const GLubyte* render = glGetString(GL_RENDERER);
        const char* glRenderChar = reinterpret_cast< const char* >(render);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);
        
        
    }
    
    void ObjectManager::WindowManager::showWindow(void) noexcept{
        SDL_ShowWindow(this->window);
    }
    
    void ObjectManager::WindowManager::finalizeWindow(void) noexcept{
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }
    
    SDL_Window* ObjectManager::WindowManager::getWindow(void) noexcept{
        return this->window;
    }
    
}
#endif /* sge_window_h */
