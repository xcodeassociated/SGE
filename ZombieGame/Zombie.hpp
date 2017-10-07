//
//  Zombie.hpp
//  SimpleGameEngine
//
//  Created by Hamashy on 16.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef Zombie_h
#define Zombie_h

#include "Agent.hpp"

class Zombie : public Agent{
    
    Human* getNearestHuman(std::vector<Human*>& humans){
        Human* closestHuman = nullptr;
        float smallestDistance = 999999.0f;
        
        std::for_each(humans.begin(), humans.end(), [&](auto& e){
        
            glm::vec2 distVec = e->getPosition() - this->position;
            float distance = glm::length(distVec);
            
            if (distance < smallestDistance){
                smallestDistance = distance;
                closestHuman = e;
            }
        });
        
        return closestHuman;
    }
    
public:
    Zombie(){
        ;
    }
    
    ~Zombie(){
        ;
    }
    
    void init(float _speed, glm::vec2 _position){
        this->speed = _speed;
        this->position = _position;
        this->color = SGE::Color(0, 160, 0, 255);
        this->health = 100;
    
    }
    
    virtual void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) override {
        
        /* chase the nearest human */
        Human* closestHuman = this->getNearestHuman(humans);
        if (closestHuman != nullptr){
            glm::vec2 direction = glm::normalize(closestHuman->getPosition() - this->position);
            this->position += direction * this->speed;
        }
        
        //check for level colision
        this->collideWithLevel(levelData);
    }
};

#endif /* Zombie_h */
