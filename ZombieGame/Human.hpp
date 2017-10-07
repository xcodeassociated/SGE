//
//  Human.hpp
//  SimpleGameEngine
//
//  Created by Hamashy on 16.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef Human_h
#define Human_h

#include "Agent.hpp"

#include <random>
#include <ctime>

class Human : public Agent{
    glm::vec2 direction;
    int frames = 0;
    
public:
    
    Human(){
        
    }
    
    void init(float _speed, glm::vec2 _position){
        this->speed = _speed;
        this->position = _position;
        this->color = SGE::Color(200, 0, 200, 255);
        this->health = 20;
        
        static std::mt19937 randomengine(std::time(nullptr));
        static std::uniform_real_distribution<float> rd(-1.0f, 1.0f);
        
        this->direction = glm::vec2(rd(randomengine), rd(randomengine));
        
        //direction can't be zero
        if (this->direction.length() == 0) this->direction = glm::vec2(1.0f, 0.0f);
        
        this->direction = glm::normalize(this->direction);
    }
    
    virtual ~Human(){
        ;
    }

    virtual void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) override {
        this->position += this->direction * this->speed;
    
        //rotate the vector position in every 20 farames to simulate the direction change
        static std::mt19937 randomengine(std::time(nullptr));
        static std::uniform_real_distribution<float> rd(-55.0f/180.0f, 55.0f/180.0f);
        
        if (this->frames == 60){
            this->direction = glm::rotate(this->direction, rd(randomengine));
            this->frames = 0;
        }else
            this->frames++;
        
        
        //standard collision with level check and if the humen has collied rotate...
        if (this->collideWithLevel(levelData)){
            this->direction = glm::rotate(this->direction, rd(randomengine));
        }
    }
};

#endif /* Human_h */
