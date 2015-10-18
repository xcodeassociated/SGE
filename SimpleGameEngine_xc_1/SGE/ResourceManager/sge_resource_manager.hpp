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
        
        ResourceManager() : textureCache(SGE::TextureCache::getSingleton()){
            std::cout << ">>    ResourceManager c-tor" << std::endl;
        };
        ResourceManager( const ResourceManager & ) : textureCache(SGE::TextureCache::getSingleton()){
            std::cout << ">>    ResourceManager c-tor" << std::endl;
        };
       
    public:
        static int arc;

        static ResourceManager* getSingleton(){
            static ResourceManager* singleton = new ResourceManager();
            SGE::ResourceManager::arc++;
            
            return singleton;
        }

        ~ResourceManager(){
            if (SGE::ResourceManager::arc == 0){
                std::cout << ">>    ResourceManager singleton deleted!" << std::endl;
                
                delete this->textureCache;
            }
            
        }
        
        SGE::GLTexture getTexture(const char* texture){
            return this->textureCache->getTexture(texture);
        }
        
    };
    
   int SGE::ResourceManager::arc = 0;
}

#endif /* sge_resource_manager_h */
