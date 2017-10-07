////
////  MainGameWindow.hpp
////  SimpleGameEngine_xc_1
////
////  Created by Hamashy on 16.10.2015.
////  Copyright © 2015 Hamashy. All rights reserved.
////
//
#ifndef MainGameWindow_h
#define MainGameWindow_h
//
//#include "../SimpleGameEngine/SGE/include/sge_include.hpp"
//#include "../SimpleGameEngine/SGE/Shaders/sge_shader.hpp"
//#include "../SimpleGameEngine/SGE/Camera2d/sge_camera2d.hpp"
//#include "../SimpleGameEngine/SGE/SpriteBatch/SpriteBatch.hpp"
//
//#include "../SimpleGameEngine/SGE/ResourceManager/sge_resource_manager.hpp"
//#include "../SimpleGameEngine/SGE/TextureLoader/sge_glTexture.hpp"
//#include "../SimpleGameEngine/SGE/InputManager/sge_input_manager.hpp"
//#include "../SimpleGameEngine/SGE/Timing/sge_fps_limiter.hpp"
//
//
//enum class GameState {
//    PLAY,
//    EXIT
//};
//
//class MainGameWindow{
//    SDL_Window* mainWindow = nullptr;
//    GameState gameState;
//    SGE::Shader* shaderProgram = nullptr;
//    int mainWindowPosX = 0, mainWindowPosY = 0;
//    int mainWindowWidth = 0, mainWindowHeight = 0;
//    bool isInited = false;
//    float time = 0, fps = 0;
//
//    SGE::Camera2d* camera = nullptr;
//    SGE::SpriteBatch* spriteBatch = nullptr;
//    SGE::ResourceManager* rm = nullptr;
//    SGE::InputManager* inputManager = nullptr;
//    SGE::FpsLimiter* fps_limiter = nullptr;
//
//    void processInput(){
//        SDL_Event event;
//        while (SDL_PollEvent(&event)){
//            switch (event.type) {
//                case SDL_QUIT:{
//                    this->gameState = GameState::EXIT;
//                }break;
//
//                case SDL_MOUSEMOTION:{
//                    this->inputManager->setMouseCoords(event.motion.x, event.motion.y);
//                }break;
//
//                case SDL_MOUSEBUTTONDOWN:{
//                    this->inputManager->pressKey(event.button.button);
//                    this->inputManager->setMouseCoords(event.motion.x, event.motion.y);
//
//                    glm::vec2 coords = this->camera->screenToWorld(this->inputManager->getMouseCoords());
//                    std::cout << "Clicked: x=" << coords.x << ", y=" << coords.y << std::endl;
//                }break;
//
//                case SDL_MOUSEBUTTONUP:{
//                    this->inputManager->releaseKey(event.button.button);
//                }break;
//
//                case SDL_KEYDOWN:{
//                    this->inputManager->pressKey(event.key.keysym.sym);
//                }break;
//
//                case SDL_KEYUP:{
//                    this->inputManager->releaseKey(event.key.keysym.sym);
//                }break;
//            }
//        }
//
//        const float CAMERA_SPEED = 2.0f;
//        const float SCALE_SPEED = 0.1f;
//
//        if (this->inputManager->isKeyPressed(SDLK_s)) {
//            this->camera->setPosition(this->camera->getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
//        }
//        if (this->inputManager->isKeyPressed(SDLK_w)) {
//            this->camera->setPosition(this->camera->getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
//        }
//        if (this->inputManager->isKeyPressed(SDLK_d)) {
//            this->camera->setPosition(this->camera->getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
//        }
//        if (this->inputManager->isKeyPressed(SDLK_a)) {
//            this->camera->setPosition(this->camera->getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
//        }
//        if (this->inputManager->isKeyPressed(SDLK_q)) {
//            this->camera->setScale(this->camera->getScale() + SCALE_SPEED);
//        }
//        if (this->inputManager->isKeyPressed(SDLK_e)) {
//            this->camera->setScale(this->camera->getScale() - SCALE_SPEED);
//        }
//
//        if (this->inputManager->isKeyPressed(SDL_BUTTON_LEFT)){
//            //
//            glm::vec2 coords = this->camera->screenToWorld(this->inputManager->getMouseCoords());
//            std::cout << "Clicked: x=" << coords.x << ", y=" << coords.y << std::endl;
//        }
//    }
//
//    void gameDrawer(){
//        glClearDepth(1.0);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        this->shaderProgram->use();
//
//        glActiveTexture(GL_TEXTURE0);
//        GLint textureLocation = this->shaderProgram->getUniformLocation("mySampler");
//        glUniform1i(textureLocation, 0);
//
////        GLint timeLocation = this->shaderProgram->getUniformLocation("time");
////        glUniform1f(timeLocation, this->time);
//
//        //Camera matrix for vertex
//        GLint pLocation = this->shaderProgram->getUniformLocation("P");
//        glm::mat4 cameraMatrix = this->camera->getCameraMatrix();
//        glUniformMatrix4fv(pLocation, 1, GL_FALSE, &( cameraMatrix[0][0] ));
//
//
//        { //Sprites:
//
//            this->spriteBatch->begin();
//
//                glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
//                glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
//                static SGE::GLTexture texture = rm->getTexture(PATH"SGE_Demo/Resources/jimmyJump_pack/PNG/CharacterRight_Standing.png");
//                SGE::Color color(255, 255, 255, 255);
//
//            this->spriteBatch->draw(pos, uv, texture.id, 0.0f, color);
//
//            this->spriteBatch->end();
//            this->spriteBatch->renderBatch();
//
//            glBindTexture(GL_TEXTURE_2D, 0);
//
//        }
//
//        this->shaderProgram->unuse();
//
//        SDL_GL_SwapWindow(this->mainWindow);
//    }
//
//public:
//    MainGameWindow(int res_x, int res_y) : mainWindowWidth(res_x),
//                                           mainWindowHeight(res_y),
//                                           camera(new SGE::Camera2d(res_x, res_y)),
//                                           spriteBatch(new SGE::SpriteBatch()),
//                                           rm(SGE::ResourceManager::getSingleton()),
//                                           inputManager(new SGE::InputManager()),
//                                           fps_limiter(new SGE::FpsLimiter()){
//
//    }
//
//    ~MainGameWindow(){
//        delete this->shaderProgram;
//        delete this->camera;
//        delete this->spriteBatch;
//        delete this->inputManager;
//        delete this->fps_limiter;
//        rm->kill();
//
//        SDL_DestroyWindow(this->mainWindow);
//        SDL_Quit();
//
//    }
//
//    void init(){
//        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
//            throw "error:    SDL_init";
//
//        this->mainWindowPosX = SDL_WINDOWPOS_CENTERED;
//        this->mainWindowPosY = SDL_WINDOWPOS_CENTERED;
//        this->gameState = GameState::PLAY;
//        this->isInited = true;
//
//        std::cout << ">>    GameEngine initialized: "                    << std::endl
//                    << "    -> glew: " << glewGetString(GLEW_VERSION)    << std::endl
//                    << "    -> glm: " << GLM_VERSION_MAJOR << "." << GLM_VERSION_MINOR << "." << GLM_VERSION_PATCH << std::endl
//                    << "    -> boost: " << BOOST_LIB_VERSION             << std::endl
//                    << "    -> " << websocketpp::user_agent              << std::endl
//                    << "    -> rapidJSON: " << RAPIDJSON_MAJOR_VERSION << "." << RAPIDJSON_MINOR_VERSION << std::endl << std::endl;
//
//    }
//
//    void initShader(){
//        this->shaderProgram = new SGE::Shader();
//
//        this->shaderProgram->doShaders(VERT, FRAG);
//
//        this->shaderProgram->addAttribute("vertexPosition");
//        this->shaderProgram->addAttribute("vertexColor");
//        this->shaderProgram->addAttribute("vertexUV");
//
//        this->shaderProgram->linkShaders();
//    }
//
//    /* MainGame Loop */
//    void run(){
//
//        this->initShader();
//        this->spriteBatch->init();
//
//        while (this->gameState != GameState::EXIT){
//            this->fps_limiter->begin();
//
//                this->processInput();
//                this->camera->update();
//                this->gameDrawer();
//
//                this->time += 0.01f;
//
//            this->fps = this->fps_limiter->end();
//            static int frameCounter = 0;
//            frameCounter++;
//            if (frameCounter == 100){
//                std::cout << "fps: " << this->fps << std::endl;
//                frameCounter = 0;
//            }
//
//        };
//    }
//
//    void show(){
//        if (this->isInited){
//            this->mainWindow = SDL_CreateWindow("SGE", this->mainWindowPosX, this->mainWindowPosY, this->mainWindowWidth, this->mainWindowHeight, SDL_WINDOW_OPENGL);
//
//            if (this->mainWindow == nullptr)
//                throw "error: ";
//
//            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//
//            SDL_GLContext glContext = SDL_GL_CreateContext(this->mainWindow);
//            if (glContext == nullptr) throw "";
//
//            glewExperimental = GL_TRUE;
//            GLenum glewCheck = glewInit();
//            if (glewCheck != GLEW_OK) throw "";
//
//            glClearColor(1.f, 1.f, 1.f, 1.0f);
//
//            //vsync
//            SDL_GL_SetSwapInterval(1);
//
//                const GLubyte* version = glGetString(GL_VERSION);
//                const char* glVersionChar = reinterpret_cast< const char* >(version);
//
//                const GLubyte* render = glGetString (GL_RENDERER);
//                const char* glRenderChar = reinterpret_cast< const char* >(render);
//
//                std::cout << "    -> OpenGl version: " << glVersionChar << std::endl;
//                std::cout << "    -> Render Device: " << glRenderChar << std::endl << std::endl;
//
//
//            glEnable(GL_BLEND);
//            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//            GLuint VertexArrayID;
//            glGenVertexArrays(1 , &VertexArrayID);
//            glBindVertexArray(VertexArrayID);
//
//            SDL_ShowWindow(this->mainWindow);
//
//        }
//    }
//
//};
//
//
//
#endif /* MainGameWindow_h */

