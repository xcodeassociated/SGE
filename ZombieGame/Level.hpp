//
//  Level.hpp
//  SimpleGameEngine
//
//  Created by Hamashy on 16.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef Level_h
#define Level_h

#include "../SimpleGameEngine/SGE/include/sge_include.hpp"
#include "../SimpleGameEngine/SGE/SpriteBatch/SpriteBatch.hpp"
#include "../SimpleGameEngine/SGE/TextureLoader/sge_glTexture.hpp"
#include "../SimpleGameEngine/SGE/ResourceManager/sge_resource_manager.hpp"

class Level{
    std::vector<std::string> levelData;
    int humans;
    bool isLoaded = false;
    
    glm::vec2 playerStratPosition;
    std::vector<glm::vec2> zombieStartPosition;
    
    const int TILE_WIDTH = 64;
    
public:
    Level(const char* filename) {
        std::ifstream file;
        file.open(filename);
        
        if (!file.fail()){
            std::string temp;
            file >> temp >> this->humans;
            temp.clear();
            
            //get rid of the first line
            std::getline(file, temp);
            
            while (std::getline(file, temp)){
                this->levelData.push_back(temp);
            }
            
            //init starting positions for player and zombies
            for (int y = 0; y < this->levelData.size(); y++){
                for (int x = 0; x < this->levelData[y].size(); x++){
                    char tile = this->levelData[y][x];
                    switch (tile){
                        case '@':{
                            this->levelData[y][x] = '.';
                            this->playerStratPosition.x = x * TILE_WIDTH;
                            this->playerStratPosition.y = y * TILE_WIDTH;
                        }break;
                        case 'Z':{
                            this->levelData[y][x] = '.';
                            this->zombieStartPosition.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
                        }break;
                        default:{}break;
                    }
                }
            }
        }else
            throw "";
        
    };
    
    const int& getHumensNumber() const {
        return this->humans;
    }
    
    const std::vector<std::string>& getLevelData() const {
        return this->levelData;
    }
    
    const glm::vec2& getPlayerPosition() const {
        return this->playerStratPosition;
    }
    
    const std::vector<glm::vec2>& getZombiePositions() const {
        return this->zombieStartPosition;
    }
    
    void load(SGE::ResourceManager* rm, SGE::SpriteBatch* spriteBatch){
        static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
        static SGE::Color color(255, 255, 255, 255);
        
        for (int y = 0; y < this->levelData.size(); y++){
            for (int x = 0; x < this->levelData[y].size(); x++){
                
                char tile = this->levelData[y][x];
                glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
                
                switch (tile){
                    case 'B' :
                    case 'R' :{
                        static SGE::GLTexture texture = rm->getTexture(PATH"ZombieGame/Resources/Textures/red_bricks.png");
                        spriteBatch->draw(destRect, uv, texture.id, 0.0f, color);
                    }break;
                    case 'G' :{
                        static SGE::GLTexture texture = rm->getTexture(PATH"ZombieGame/Resources/Textures/glass.png");
                        spriteBatch->draw(destRect, uv, texture.id, 0.0f, color);
                    }break;
                    case 'L' :{
                        static SGE::GLTexture texture = rm->getTexture(PATH"ZombieGame/Resources/Textures/light_bricks.png");
                        spriteBatch->draw(destRect, uv, texture.id, 0.0f, color);
                    }break;
                    case '.':{
                        
                    }break;
                        
                    default:{}break;
                }
            }
        }
    }
    
    ~Level(){
    };
};

#endif /* Level_h */
