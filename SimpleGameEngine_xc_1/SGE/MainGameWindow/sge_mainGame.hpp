//
//  MainGameWindow.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 16.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef MainGameWindow_h
#define MainGameWindow_h

#include "../include/sge_include.hpp"
#include "../Sprite/sge_sprite.hpp"
#include "../Shaders/sge_shader.hpp"

namespace SGE {
    
    enum class GameState {
        PLAY,
        EXIT
    };
    
    class MainGameWindow{
        //private:
        SDL_Window* mainWindow = nullptr;
        GameState gameState;
        SGE::Shader* shaderProgram = nullptr;
        int mainWindowPosX = 0, mainWindowPosY = 0;
        int mainWindowWidth = 0, mainWindowHeight = 0;
        bool isInited = false;
        float time = 0, fps = 0, frameTime = 0, max_fps = 60;
        
        std::vector< std::tuple< SGE::Sprite*, size_t> > sprites;
        
        void processInput(){
            SDL_Event event;
            while (SDL_PollEvent(&event)){
                switch (event.type) {
                    case SDL_QUIT:{
                        this->gameState = GameState::EXIT;
                        std::cout << ">>    Window close call!" << std::endl;
                    }break;
                        
                    case SDL_MOUSEMOTION:{
                        //std::cout << " x: " << event.motion.x << " y: " << event.motion.y << std::endl;
                    }break;
                        
                    case SDL_MOUSEBUTTONDOWN:{
                        //...
                    }break;
                        
                    default:{}break;
                }
            }
            
        }
        
        void gameDrawer(){
            glClearDepth(1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            this->shaderProgram->use();
            
            glActiveTexture(GL_TEXTURE0);
            GLint textureLocation = this->shaderProgram->getUniformLocation("mySampler");
            glUniform1i(textureLocation, 0);
            
            //GLint timeLocation = this->shaderProgram->getUniformLocation("time");
            //glUniform1f(timeLocation, this->time);
            
            {
                //draw all sprites
                std::for_each(this->sprites.begin(), this->sprites.end(), [](std::tuple<SGE::Sprite*, size_t>& element){
                    (std::get<0>(element))->draw();
                });
            }
            
            glBindTexture(GL_TEXTURE_2D, 0);
            
            this->shaderProgram->unuse();
            
            SDL_GL_SwapWindow(this->mainWindow);
        }
        
        void calculateFPS(){
            static const int NUM_SAMPLES = 10;
            static float frameTimes[NUM_SAMPLES];
            static int currentFrame = 0;
            
            static float prevTicks = SDL_GetTicks();
            
            float currentTick = SDL_GetTicks();
            
            //ok first take is gone be incorrect
            this->frameTime = currentTick - prevTicks;
            frameTimes[currentFrame % NUM_SAMPLES] = this->frameTime;
            
            prevTicks = currentTick;
            
            int count;
            currentFrame++;
            
            if (currentFrame < NUM_SAMPLES)
                count = currentFrame;
            else
                count = NUM_SAMPLES;
            
            float frameTimeAverage = 0;
            for (int i = 0; i < count; i++)
                frameTimeAverage += frameTimes[i];
            
            frameTimeAverage /= count;
            
            if (frameTimeAverage > 0)
                this->fps = 1000.0f / frameTimeAverage;
            else
                this->fps = 60.0f;
            
        }
        
    public:
        MainGameWindow(int res_x, int res_y) : mainWindowWidth(res_x), mainWindowHeight(res_y){
            std::cout << ">>    MainGameWindow constructed!" << std::endl;
        }
        
        ~MainGameWindow(){
            
            std::for_each(this->sprites.begin(), this->sprites.end(), [](std::tuple<SGE::Sprite*, size_t>& element){
                delete std::get<0>(element);
            });
            
            delete this->shaderProgram;
            
            SDL_DestroyWindow(this->mainWindow);
            SDL_Quit();
            
            std::cout << ">>    MainGameWindow deconstructed!" << std::endl;
        }
        
        void init(){
            if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "error:    SDL_init";
            
            this->mainWindowPosX = SDL_WINDOWPOS_CENTERED;
            this->mainWindowPosY = SDL_WINDOWPOS_CENTERED;
            this->gameState = GameState::PLAY;
            this->isInited = true;
            
            std::cout << ">>    GameEngine initialized: "                    << std::endl
                        << "    -> glew: " << glewGetString(GLEW_VERSION)    << std::endl
                        << "    -> boost: " << BOOST_LIB_VERSION             << std::endl
                        << "    -> " << websocketpp::user_agent              << std::endl
                        << "    -> rapidJSON: " << RAPIDJSON_MAJOR_VERSION << "." << RAPIDJSON_MINOR_VERSION << std::endl
                        << std::endl;
            
            
        }
        
        void initShader(){
            this->shaderProgram = new SGE::Shader();
            
            this->shaderProgram->doShaders("/Users/Hamashy/Desktop/GameEngine.repo/SimpleGameEngine_xc_1/SGE/Shaders/res/colorShader.vert",
                                           "/Users/Hamashy/Desktop/GameEngine.repo/SimpleGameEngine_xc_1/SGE/Shaders/res/colorShader.frag");
            
            this->shaderProgram->addAttribute("vertexPosition");
            this->shaderProgram->addAttribute("vertexColor");
            this->shaderProgram->addAttribute("vertexUV");
            
            this->shaderProgram->linkShaders();
        }
        
        
        void run(){
            this->initShader();
            
            while (this->gameState != GameState::EXIT){
                float startTicks = SDL_GetTicks();
                
                this->processInput();
                this->gameDrawer();
                this->time += 0.01f;
                
                this->calculateFPS();
                
                static int frames = 0;
                frames++;
                
                if (frames == 150){
                    std::cout << "fps: " << this->fps << std::endl;
                    frames = 0;
                }
                
                float framesTicks = SDL_GetTicks() - startTicks;
                
                if ((1000.0f / this->max_fps) > framesTicks)
                    SDL_Delay((1000.0f / this->max_fps) - framesTicks);
            };
            
            //do something with the window...
            
            std::cout << ">>    GameLoop brake" << std::endl;
        }
        
        void show(){
            if (this->isInited){
                this->mainWindow = SDL_CreateWindow("SGE", this->mainWindowPosX, this->mainWindowPosY, this->mainWindowWidth, this->mainWindowHeight, SDL_WINDOW_OPENGL);
                
                if (this->mainWindow == nullptr) throw "error: ";
                
                SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                
                SDL_GLContext glContext = SDL_GL_CreateContext(this->mainWindow);
                if (glContext == nullptr) throw "";
                
                glewExperimental = GL_TRUE;
                GLenum glewCheck = glewInit();
                if (glewCheck != GLEW_OK) throw "";
                
                glClearColor(0.f, 0.f, 0.f, 1.0f);
                
                //vsync
                SDL_GL_SetSwapInterval(1);
                
                
                    const GLubyte* version = glGetString(GL_VERSION);
                    const char* glVersionChar = reinterpret_cast< const char* >(version);
                    
                    const GLubyte* render = glGetString (GL_RENDERER);
                    const char* glRenderChar = reinterpret_cast< const char* >(render);
                    
                    std::cout << ">>    OpenGl version: " << glVersionChar << std::endl;
                    std::cout << ">>    Render Device: " << glRenderChar << std::endl << std::endl;
                
                
                GLuint VertexArrayID;
                glGenVertexArrays(1 , &VertexArrayID);
                glBindVertexArray(VertexArrayID);
                
                SDL_ShowWindow(this->mainWindow);
                
            }else
                std::cout << ">>    init first!" << std::endl;
        }
        
        void addSprite(SGE::Sprite* _sprite, size_t _tag){
            if (_sprite == nullptr && _sprite->isInited()) throw "";
            
            this->sprites.push_back(std::make_tuple(_sprite, _tag));
        }
        
    };
    
}

#endif /* MainGameWindow_h */
