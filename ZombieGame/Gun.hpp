//
//  Gun.hpp
//  SimpleGameEngine
//
//  Created by Hamashy on 18.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef Gun_h
#define Gun_h

#include "../SimpleGameEngine/SGE/include/sge_include.hpp"
#include "Bullet.hpp"

class Gun{
    int fireRate = 0;
    float spead = 0;
    int bulletsPerShot = 0;
    std::string name;
    float bulletSpeed = 0, bulletDamage = 0;
    
    int frameCounter = 0;
    
    void fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets){
        static std::mt19937 randomengine(std::time(nullptr));
        std::uniform_real_distribution<float> rd(-(this->spead)/180.0f, this->spead/180.0f);
        
        for (int i = 0; i < this->bulletsPerShot; i++){
            bullets.emplace_back(position, glm::rotate(direction, rd(randomengine)), this->bulletDamage, this->bulletSpeed);
        }
    }
    
public:
    Gun(std::string _name, int _fireRate, int _bulletsPerShot, float _spread, float _bulletDamage, float _bulletSpeed) :
    fireRate(_fireRate),
    name(_name),
    bulletsPerShot(_bulletsPerShot),
    spead(_spread),
    bulletSpeed(_bulletSpeed),
    bulletDamage(_bulletDamage){
        
    }
    
    ~Gun(){
        
    }
    
    void update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets){
        this->frameCounter++;
        if (this->frameCounter >= this->fireRate && isMouseDown){
            this->fire(position, direction, bullets);
            this->frameCounter = 0;
        }
    }
    
   
};

#endif /* Gun_h */
