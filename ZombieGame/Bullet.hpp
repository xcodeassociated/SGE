//
//  Bullet.hpp
//  SimpleGameEngine
//
//  Created by Hamashy on 13.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef Bullet_h
#define Bullet_h

#include "../SimpleGameEngine/SGE/include/sge_include.hpp"
#include "../SimpleGameEngine/SGE/SpriteBatch/SpriteBatch.hpp"
#include "../SimpleGameEngine/SGE/TextureLoader/sge_glTexture.hpp"
#include "../SimpleGameEngine/SGE/ResourceManager/sge_resource_manager.hpp"

#include "Agent.hpp"

class Bullet{
    glm::vec2 position;
    glm::vec2 direction;
    float speed = 0, damage = 0;
    int BULLET_RADIUS = 5;
    
public:
    Bullet(glm::vec2 _position, glm::vec2 _direction, float _damage, float _speed) :
    position(_position),
    direction(_direction),
    speed(_speed),
    damage(_damage){
        
    }
    
    ~Bullet(){
        
    }
    
    const float& getDamage(){
        return this->damage;
    }
    
    bool update(const std::vector<std::string>& levelData){
        this->position += this->direction * this->speed;
        return collideWithWorld(levelData);
    };
    
    void draw(SGE::ResourceManager* rm, SGE::SpriteBatch* spriteBatch){
        glm::vec4 destRect(this->position.x + BULLET_RADIUS,
                           this->position.y + BULLET_RADIUS,
                           BULLET_RADIUS * 2,
                           BULLET_RADIUS * 2);
        
        const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
        
        SGE::Color color(75, 75, 75, 255);
        static SGE::GLTexture texture = rm->getTexture(PATH"ZombieGame/Textures/circle.png");

        
        spriteBatch->draw(destRect, uvRect, texture.id, 0.0f, color);
    }
    
    bool collideWithAgent(Agent* agent) {
        const float AGENT_RADIUS = 30.0f;
        const int BULLET_RADIUS = 5;
        const float MIN_DISTANCE = AGENT_RADIUS + BULLET_RADIUS;
        
        glm::vec2 centerPosA = this->position;
        glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);
        
        glm::vec2 distVec = centerPosA - centerPosB;
        
        float distance = glm::length(distVec);
        
        float collisionDepth = MIN_DISTANCE - distance;
        if (collisionDepth > 0) {
            return true;
        }
        return false;
    }
    
    bool collideWithWorld(const std::vector<std::string>& levelData) {
        const int TILE_WIDTH = 64;

        glm::ivec2 gridPosition;
        gridPosition.x = floor(this->position.x / (float)TILE_WIDTH);
        gridPosition.y = floor(this->position.y / (float)TILE_WIDTH);
        
        // If we are outside the world, just return
        if (gridPosition.x < 0 || gridPosition.x >= levelData[0].size() ||
            gridPosition.y < 0 || gridPosition.y >= levelData.size()) {
            return true;
        }
        
        return (levelData[gridPosition.y][gridPosition.x] != '.');
    }
};

#endif /* Bullet_h */
