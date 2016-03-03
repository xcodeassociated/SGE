//
//  Agent.hpp
//  SimpleGameEngine
//
//  Created by Hamashy on 16.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef Agent_h
#define Agent_h

#include "../SimpleGameEngine/SGE/include/sge_include.hpp"
#include "../SimpleGameEngine/SGE/SpriteBatch/SpriteBatch.hpp"
#include "../SimpleGameEngine/SGE/TextureLoader/sge_glTexture.hpp"
#include "../SimpleGameEngine/SGE/ResourceManager/sge_resource_manager.hpp"

/* this prevents the circular includes */
class Zombie;
class Human;

class Agent{
protected:
    glm::vec2 position;
    float speed;
    const int AGENT_WITHD = 60;
    const int TILE_WIDTH = 64;
    SGE::Color color;
    float health;
    
public:
    virtual ~Agent(){
        ;
    }
    
    void draw(SGE::ResourceManager* rm, SGE::SpriteBatch* spriteBatch){
        
        glm::vec4 pos(this->position.x, this->position.y, AGENT_WITHD, AGENT_WITHD);
        static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
        static SGE::GLTexture texture = rm->getTexture(PATH"ZombieGame/Textures/circle.png");
       
        spriteBatch->draw(pos, uv, texture.id, 0.0f, this->color);
    }
    
    const glm::vec2& getPosition() const {
        return this->position;
    }
    
    //AABB collision
    void collideWithTile(glm::vec2 tilePosition){
        
        const float AGENT_RADIUS = (float)AGENT_WITHD / 2.0f;
        const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
        const float MIN_DIST = AGENT_RADIUS + TILE_RADIUS;

        glm::vec2 centerPlayerPosition = this->position + glm::vec2(AGENT_RADIUS);
        glm::vec2 dist = centerPlayerPosition - tilePosition;
        
        float xDepth = MIN_DIST - std::abs(dist.x);
        float yDepth = MIN_DIST - std::abs(dist.y);
        
        //if true - collision
        if (xDepth > 0 && yDepth > 0){
            if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)){
                if (dist.x < 0)
                    this->position.x -= xDepth;
                else
                    this->position.x += xDepth;
            }else{
                if (dist.y < 0)
                    this->position.y -= yDepth;
                else
                    this->position.y += yDepth;
            }
        }
    }
    
    void checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePosition, float x, float y){
        glm::vec2 cornerPosition = glm::vec2(std::floor(x / (float)TILE_WIDTH), std::floor(y / (float)TILE_WIDTH));
        
        if (cornerPosition.x < 0 || cornerPosition.x >= levelData[0].size() || cornerPosition.y < 0 || cornerPosition.y >= levelData.size()){
            return;
        }
        
        if (levelData[cornerPosition.y][cornerPosition.x] != '.')
            collideTilePosition.push_back(cornerPosition * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
    }
    
    bool collideWithLevel(const std::vector<std::string>& levelData){
        std::vector<glm::vec2> collideTilePosition{};
        
        //check 4 corners
        
        //first
        this->checkTilePosition(levelData, collideTilePosition, this->position.x, this->position.y);
        //second
        this->checkTilePosition(levelData, collideTilePosition, this->position.x + AGENT_WITHD, this->position.y);
        //third
        this->checkTilePosition(levelData, collideTilePosition, this->position.x, this->position.y + AGENT_WITHD);
        //fourth
        this->checkTilePosition(levelData, collideTilePosition, this->position.x + AGENT_WITHD, this->position.y + AGENT_WITHD);
        
        if (collideTilePosition.size() == 0)
            return false;
        
        //do the collision
        std::for_each(collideTilePosition.begin(), collideTilePosition.end(), [&](auto& e){
            this->collideWithTile(e);
        });
        
        return true;
    }
    
    bool collideWithAgent(Agent* agent){
        const float AGENT_RADIUS = (float)AGENT_WITHD / 2.0f;
        const float MIN_DIST = AGENT_RADIUS * 2;
        glm::vec2 centerPosA = this->position + glm::vec2(AGENT_RADIUS);
        glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);
        
        glm::vec2 distVec = centerPosA - centerPosB;

        float distLength = glm::length(distVec);
        
        float collisionDepth = MIN_DIST - distLength;
        
        //we have a collision - push 'em 
        if (collisionDepth > 0){
            glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;
            
            this->position += collisionDepthVec / 2.0f;
            agent->position -= collisionDepthVec / 2.0f;
            
            return true;
        }else
            return false;
    }
    
    virtual void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) = 0;
    
    bool applyDamage(float _damage){
        this->health -= _damage;
        return (this->health <= 0);
    }
    
};

#endif /* Agent_h */
