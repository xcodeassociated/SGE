//
//  sge_resource_manager.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_resource_manager_h
#define sge_resource_manager_h

#include "../include/sge_include.hpp"
#include "../TextureCache/sge_texture_cache.hpp"
#include "../TextureLoader/sge_glTexture.hpp"

namespace SGE {
    
    class ResourceManager{
        SGE::TextureCache* textureCache = nullptr;
    
        static ResourceManager* p_inst;
        static int arc;

        ResourceManager() : textureCache(SGE::TextureCache::getSingleton()){
            std::cout << ">>    ResourceManager c-tor" << std::endl;
        };
        ResourceManager( const ResourceManager & ) : textureCache(SGE::TextureCache::getSingleton()){
            std::cout << ">>    ResourceManager c-tor" << std::endl;
        };
        
        ~ResourceManager(){
            this->textureCache->kill();
            this->textureCache = nullptr;
            SGE::ResourceManager::p_inst = nullptr;
        }
       
    public:
        static ResourceManager* getSingleton(){
            SGE::ResourceManager::arc++;
            
            if (!p_inst){
                ResourceManager::p_inst = new ResourceManager();
            }
            return p_inst;
        }
        
        void kill(){
            SGE::ResourceManager::arc--;
            
            if (SGE::ResourceManager::arc == 0){
                std::cout << ">>    ResourceManager singleton deleted!" << std::endl;
                
                delete this;
            }
            
        }
        
        SGE::GLTexture getTexture(const char* texture){
            return this->textureCache->getTexture(texture);
        }
        
    };
    
    int SGE::ResourceManager::arc = 0;
    SGE::ResourceManager* SGE::ResourceManager::p_inst = nullptr;

}

#endif /* sge_resource_manager_h */
