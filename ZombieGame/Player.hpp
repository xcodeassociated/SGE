//
//  Player.hpp
//  SimpleGameEngine
//
//  Created by Hamashy on 16.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include "Human.hpp"
#include "../SimpleGameEngine/SGE/InputManager/sge_input_manager.hpp"
#include "../SimpleGameEngine/SGE/Camera2d/sge_camera2d.hpp"

#include "Gun.hpp"

class Player : public Human{
    SGE::InputManager* inputManager = nullptr;
    std::vector<Gun*> guns;
    int currentGun = -1;
    SGE::Camera2d* camera = nullptr;
    
public:
    Player(int _speed, glm::vec2 _position, SGE::InputManager* _inputManager, SGE::Camera2d* _camera) :
    inputManager(_inputManager),
    camera(_camera){
        this->speed = _speed;
        this->position = _position;
        this->color = SGE::Color(0, 0, 128, 255);
    }
    
    ~Player(){
    }
    
    void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Bullet>& bullets) {
        if (this->inputManager->isKeyPressed(SDLK_s)) {
            this->position.y -= this->speed;
        }
        if (this->inputManager->isKeyPressed(SDLK_w)) {
            this->position.y += this->speed;
        }
        if (this->inputManager->isKeyPressed(SDLK_d)) {
            this->position.x += this->speed;
        }
        if (this->inputManager->isKeyPressed(SDLK_a)) {
            this->position.x -= this->speed;
        }
        
        if (this->inputManager->isKeyPressed(SDLK_1) && this->guns.size() > 0){
            this->currentGun = 0;
        } else if (this->inputManager->isKeyPressed(SDLK_2) && this->guns.size() > 1){
            this->currentGun = 1;
        } else if (this->inputManager->isKeyPressed(SDLK_0)){
            this->currentGun = -1;
        }
        
        if (this->currentGun != -1){
            glm::vec2 coords = this->camera->screenToWorld(this->inputManager->getMouseCoords());
            glm::vec2 centerPosition = this->position + glm::vec2(30.0f);
            glm::vec2 direction = glm::normalize(coords - centerPosition);
            this->guns[this->currentGun]->update(this->inputManager->isKeyPressed(SDL_BUTTON_LEFT), centerPosition, direction, bullets);
        }
        
        this->collideWithLevel(levelData);
    }
    
    void addGun(Gun* _gun){
        this->guns.push_back(_gun);
        
        if (this->currentGun == -1)
            this->currentGun = 0;
    }
};

#endif /* Player_h */
