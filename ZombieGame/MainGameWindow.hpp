//
//  MainGameWindow.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 16.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef MainGameWindow_h
#define MainGameWindow_h

#include "../SimpleGameEngine/SGE/include/sge_include.hpp"
#include "../SimpleGameEngine/SGE/Shaders/sge_shader.hpp"
#include "../SimpleGameEngine/SGE/Camera2d/sge_camera2d.hpp"
#include "../SimpleGameEngine/SGE/SpriteBatch/SpriteBatch.hpp"
#include "../SimpleGameEngine/SGE/ResourceManager/sge_resource_manager.hpp"
#include "../SimpleGameEngine/SGE/TextureLoader/sge_glTexture.hpp"
#include "../SimpleGameEngine/SGE/InputManager/sge_input_manager.hpp"
#include "../SimpleGameEngine/SGE/Timing/sge_fps_limiter.hpp"

#include <random>
#include <ctime>

#include "Bullet.hpp"
#include "Gun.hpp"

#include "Level.hpp"

#include "Player.hpp"
#include "Zombie.hpp"

enum class GameState {
    PLAY,
    EXIT
};

class MainGameWindow{
    SDL_Window* mainWindow = nullptr;
    GameState gameState;
    SGE::Shader* shaderProgram = nullptr;
    int mainWindowPosX = 0, mainWindowPosY = 0;
    int mainWindowWidth = 0, mainWindowHeight = 0;
    bool isInited = false;
    float time = 0, fps = 0;
    
    SGE::Camera2d* camera = nullptr;
    SGE::SpriteBatch* spriteBatch = nullptr;
    SGE::ResourceManager* rm = nullptr;
    SGE::InputManager* inputManager = nullptr;
    SGE::FpsLimiter* fps_limiter = nullptr;
    
    SGE::SpriteBatch* agentsSpriteBatch = nullptr;
    
    
    Level* level = nullptr;
    
    Player* player = nullptr;
    std::vector<Human*> humans;
    std::vector<Zombie*> zombies;
    
    std::vector<Bullet> bullets;
    
    void processInput(){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:{
                    this->gameState = GameState::EXIT;
                }break;
                    
                case SDL_MOUSEMOTION:{
                    this->inputManager->setMouseCoords(event.motion.x, event.motion.y);
                }break;
                    
                case SDL_MOUSEBUTTONDOWN:{
                    this->inputManager->pressKey(event.button.button);
                    this->inputManager->setMouseCoords(event.motion.x, event.motion.y);
                    
                    glm::vec2 coords = this->camera->screenToWorld(this->inputManager->getMouseCoords());
//                    std::cout << "Clicked: x=" << coords.x << ", y=" << coords.y << std::endl;

                    /* add bullet every click */
                    glm::vec2 playerPosition(this->player->getPosition());
                    glm::vec2 direction = coords - playerPosition;
                    direction = glm::normalize(direction);
                    
                    
                }break;
                    
                case SDL_MOUSEBUTTONUP:{
                    this->inputManager->releaseKey(event.button.button);
                }break;
                
                case SDL_KEYDOWN:{
                    this->inputManager->pressKey(event.key.keysym.sym);
                }break;
            
                case SDL_KEYUP:{
                    this->inputManager->releaseKey(event.key.keysym.sym);
                }break;
            }
        }
        
        const float CAMERA_SPEED = 2.0f;
        const float SCALE_SPEED = 0.1f;
        
        /* set camera scale */
        if (this->inputManager->isKeyPressed(SDLK_q)) {
            this->camera->setScale(this->camera->getScale() + SCALE_SPEED);
        }
        if (this->inputManager->isKeyPressed(SDLK_e)) {
            this->camera->setScale(this->camera->getScale() - SCALE_SPEED);
        }
        
        
        
        if (this->inputManager->isKeyPressed(SDL_BUTTON_LEFT)){
            
            glm::vec2 coords = this->camera->screenToWorld(this->inputManager->getMouseCoords());
//            std::cout << "Clicked: x=" << coords.x << ", y=" << coords.y << std::endl;
            
            /* add bullet every click */
            glm::vec2 playerPosition(this->player->getPosition());
            glm::vec2 direction = coords - playerPosition;
            direction = glm::normalize(direction);
            
        }
    }
    
    void gameDrawer(){
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        this->shaderProgram->use();
        
        glActiveTexture(GL_TEXTURE0);
        GLint textureLocation = this->shaderProgram->getUniformLocation("mySampler");
        glUniform1i(textureLocation, 0);
        
//        GLint timeLocation = this->shaderProgram->getUniformLocation("time");
//        glUniform1f(timeLocation, this->time);
        
        //Camera matrix for vertex
        GLint pLocation = this->shaderProgram->getUniformLocation("P");
        glm::mat4 cameraMatrix = this->camera->getCameraMatrix();
        glUniformMatrix4fv(pLocation, 1, GL_FALSE, &( cameraMatrix[0][0] ));
        
        
        { /* SpriteBatches render for textures and agents: */
            
            this->agentsSpriteBatch->begin();

            /* ====================================================================================================== */
            
            //check the humans collisions..
            for (int i = 0; i < this->humans.size(); i++){
                for (int j = i + 1; j < this->humans.size(); j++){
                    this->humans[i]->collideWithAgent(this->humans[j]);
                }
            }
            
            /* draw player */
            this->player->update(this->level->getLevelData(), this->humans, this->zombies, this->bullets);
            this->player->draw(this->rm, this->agentsSpriteBatch);
            
            /* draw humans */
            std::for_each(this->humans.begin(), this->humans.end(), [&](auto& e){
                e->update(this->level->getLevelData(), this->humans, this->zombies);
                e->draw(this->rm, this->agentsSpriteBatch);
            });
            
            /* ====================================================================================================== */

            //check the zombie collisions..
            for (int i = 0; i < this->zombies.size(); i++){
                //collide with other zombies
                for (int j = i + 1; j < this->zombies.size(); j++){
                    this->zombies[i]->collideWithAgent(this->zombies[j]);
                }
                //collide with humans to turn 'em into zombie
                for (int j = 1; j < this->humans.size(); j++){ // form 1 -> skip the player
                    if (this->zombies[i]->collideWithAgent(this->humans[j])){
                        //make a new zombie
                        this->zombies.push_back(new Zombie);
                        this->zombies.back()->init(1.3f, this->humans[j]->getPosition());
                        //delet a human
                        delete this->humans[j];
                        this->humans[j] = this->humans.back();
                        this->humans.pop_back();
                    }
                }
            }
            //check zombie collision with player
            // ...
            /* zombies update and draw */
            std::for_each(this->zombies.begin(), this->zombies.end(), [&](auto& e){
                e->update(this->level->getLevelData(), this->humans, this->zombies);
                e->draw(this->rm, this->agentsSpriteBatch);
            });
            
            /* ====================================================================================================== */
            
            // update the bullets and check for level colision
            std::for_each(this->bullets.begin(), this->bullets.end(), [&](auto& e){
                if (e.update(this->level->getLevelData())){ //bullet collied with level - need to be deleted
                    e = this->bullets.back();
                    this->bullets.pop_back();
                }else
                    e.draw(this->rm, this->agentsSpriteBatch);
            });
            bool wasBulletRemoved;
            /* check for agent colision for bullet */
            for (int i = 0; i < this->bullets.size(); i++) {
                wasBulletRemoved = false;
                // Loop through zombies
                for (int j = 0; j < this->zombies.size(); ) {
                    if (this->bullets[i].collideWithAgent(this->zombies[j])) {
                        if (this->zombies[j]->applyDamage(this->bullets[i].getDamage())) {
                            delete this->zombies[j];
                            
                            this->zombies[j] = this->zombies.back();
                            this->zombies.pop_back();
                        } else {
                            j++;
                        }
                        
                        // Remove the bullet
                        this->bullets[i] = this->bullets.back();
                        this->bullets.pop_back();
                        wasBulletRemoved = true;
                        i--;
                        break;
                    } else {
                        j++;
                    }
                }
                if (wasBulletRemoved == false) {
                    for (int j = 1; j < this->humans.size(); ) {
                        if (this->bullets[i].collideWithAgent(this->humans[j])) {
                            if (this->humans[j]->applyDamage(this->bullets[i].getDamage())) {
                                delete this->humans[j];
                                
                                this->humans[j] = this->humans.back();
                                this->humans.pop_back();
                            } else {
                                j++;
                            }
                            
                            // Remove the bullet
                            this->bullets[i] = this->bullets.back();
                            this->bullets.pop_back();
                            i--;
                            break;
                        } else {
                            j++;
                        }
                    }
                }
            }

            /* ====================================================================================================== */

            this->agentsSpriteBatch->end();
            this->agentsSpriteBatch->renderBatch();
            
            /* ------------------------------------------------------------------------- */
            this->spriteBatch->begin();
            {
                /* draw the level */
                this->level->load(this->rm, this->spriteBatch);
                
            }
            this->spriteBatch->end();
            this->spriteBatch->renderBatch();
            /* ------------------------------------------------------------------------- */

        }
        
        glBindTexture(GL_TEXTURE_2D, 0);
        
        this->shaderProgram->unuse();
        
        SDL_GL_SwapWindow(this->mainWindow);
    }
    
public:
    MainGameWindow(int res_x, int res_y) :
    
    mainWindowWidth(res_x),
    mainWindowHeight(res_y),
    camera(new SGE::Camera2d(res_x, res_y)),
    spriteBatch(new SGE::SpriteBatch()),
    rm(SGE::ResourceManager::getSingleton()),
    inputManager(new SGE::InputManager()),
    fps_limiter(new SGE::FpsLimiter()),
    agentsSpriteBatch(new SGE::SpriteBatch()){
        
        /* add a player to the level on the right posiion */
        this->level = new Level(PATH"ZombieGame/Levels/level1.txt");
        this->player = new Player(4.0f, this->level->getPlayerPosition(), this->inputManager, this->camera);
        this->player->addGun(new Gun("Magnum", 30, 1, 10.0f, 30, 20.0f));
        this->player->addGun(new Gun("Shotgun", 60, 20, 40.0f, 4, 20.0f));

        this->humans.push_back(this->player);
        
        
        /* add a humans to the level on the random positions */
        const float human_speed = 1.0f;
        const int TILE_WIDTH = 64;
        
        std::mt19937 randomengine;
        randomengine.seed(std::time(nullptr));
        std::uniform_int_distribution<int> rdX(2, this->level->getLevelData()[0].size() -2); //
        std::uniform_int_distribution<int> rdY(2, this->level->getLevelData().size() -2);

        auto hum_num = this->level->getHumensNumber();
        for (int i = 0; i < hum_num; i++){
            this->humans.push_back(new Human);
            glm::vec2 hum_pos(rdX(randomengine) * TILE_WIDTH, rdY(randomengine) * TILE_WIDTH);
            this->humans.back()->init(human_speed, hum_pos);
        }
        
        
        /* add the zombie to the level on the right position */
        std::vector<glm::vec2> zombiePositions = this->level->getZombiePositions();
        const float zombie_speed = 1.3f;
        
        for (glm::vec2& e : zombiePositions){
            this->zombies.push_back(new Zombie);
            this->zombies.back()->init(zombie_speed, e);
        }
        
    }
    
    ~MainGameWindow(){
        delete this->shaderProgram;
        delete this->camera;
        delete this->inputManager;
        delete this->fps_limiter;
        rm->kill();
        
        delete this->spriteBatch;
        delete this->agentsSpriteBatch;
        delete this->level;
        
        /* deloc humans and zombies */
        std::for_each(this->humans.begin(), this->humans.end(), [&](auto& e){ //this will also delete a human at index 0
            delete e;
        });
        std::for_each(this->zombies.begin(), this->zombies.end(), [&](auto& e){
            delete e;
        });
        
        //delete bullets
        // ...
        
        SDL_DestroyWindow(this->mainWindow);
        SDL_Quit();
        
    }
    
    void init(){
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            throw "error:    SDL_init";
        
        this->mainWindowPosX = SDL_WINDOWPOS_CENTERED;
        this->mainWindowPosY = SDL_WINDOWPOS_CENTERED;
        this->gameState = GameState::PLAY;
        this->isInited = true;
        
        std::cout << ">>    GameEngine initialized: "                    << std::endl
                    << "    -> glew: " << glewGetString(GLEW_VERSION)    << std::endl
                    << "    -> glm: " << GLM_VERSION_MAJOR << "." << GLM_VERSION_MINOR << "." << GLM_VERSION_PATCH << std::endl
                    << "    -> boost: " << BOOST_LIB_VERSION             << std::endl
                    << "    -> " << websocketpp::user_agent              << std::endl
                    << "    -> rapidJSON: " << RAPIDJSON_MAJOR_VERSION << "." << RAPIDJSON_MINOR_VERSION << std::endl << std::endl;
        
    }
    
    void initShader(){
        this->shaderProgram = new SGE::Shader();
        
        this->shaderProgram->doShaders(VERT, FRAG);
        
        this->shaderProgram->addAttribute("vertexPosition");
        this->shaderProgram->addAttribute("vertexColor");
        this->shaderProgram->addAttribute("vertexUV");
        
        this->shaderProgram->linkShaders();
    }
    
    /* MainGame Loop */
    void run(){
        //init shaders
        this->initShader();
        
        //init sprite batches
        this->spriteBatch->init();
        this->agentsSpriteBatch->init();
        
        /* Main game loop... goes unitil window closed */
        while (this->gameState != GameState::EXIT){
            
            //FPS limiting!
            this->fps_limiter->begin();
            {
                /* process input by pulling event loop */
                this->processInput();
            
                /* camera update */
                this->camera->update();
                this->camera->setPosition(this->player->getPosition());
            
                /* draw function of all sprites and textures */
                this->gameDrawer();
                this->time += 0.01f;
            }
            this->fps = this->fps_limiter->end();
            
            static int frameCounter = 0;
            frameCounter++;
            if (frameCounter == 100){
                std::cout << "fps: " << this->fps << std::endl;
                frameCounter = 0;
            }

        };
    }
    
    void show(){
        if (this->isInited){
            this->mainWindow = SDL_CreateWindow("SGE", this->mainWindowPosX, this->mainWindowPosY, this->mainWindowWidth, this->mainWindowHeight, SDL_WINDOW_OPENGL);
            
            if (this->mainWindow == nullptr)
                throw "error: ";
            
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            
            SDL_GLContext glContext = SDL_GL_CreateContext(this->mainWindow);
            if (glContext == nullptr) throw "";
            
            glewExperimental = GL_TRUE;
            GLenum glewCheck = glewInit();
            if (glewCheck != GLEW_OK) throw "";
            
            glClearColor(.7f, .7f, .7f, 1.0f);
            
            //vsync
            SDL_GL_SetSwapInterval(1);
            
                const GLubyte* version = glGetString(GL_VERSION);
                const char* glVersionChar = reinterpret_cast< const char* >(version);
                
                const GLubyte* render = glGetString (GL_RENDERER);
                const char* glRenderChar = reinterpret_cast< const char* >(render);
                
                std::cout << "    -> OpenGl version: " << glVersionChar << std::endl;
                std::cout << "    -> Render Device: " << glRenderChar << std::endl << std::endl;
            
            
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            GLuint VertexArrayID;
            glGenVertexArrays(1 , &VertexArrayID);
            glBindVertexArray(VertexArrayID);
            
            SDL_ShowWindow(this->mainWindow);
            
        }
    }

};
    


#endif /* MainGameWindow_h */
