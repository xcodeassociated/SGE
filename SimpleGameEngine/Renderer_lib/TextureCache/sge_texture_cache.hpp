//
//  sge_texture_cache.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_texture_cache_h
#define sge_texture_cache_h

#include "sge_include.hpp"

#include "sge_imageLoader.hpp"

namespace SGE {

    class TextureCache{
        
        std::map<std::string, SGE::GLTexture> textureMap;

        static TextureCache* p_inst;
        static int arc;

        TextureCache(){
            //std::cout << ">>    TextureCache c-tor" << std::endl;
        };
        
        TextureCache( const TextureCache & ){
            //std::cout << ">>    TextureCache c-tor" << std::endl;
        };
        
        ~TextureCache(){
            SGE::TextureCache::p_inst = nullptr;
        }
        
    public:
        static TextureCache* getSingleton(){
            SGE::TextureCache::arc++;
            
            if (!p_inst){
                TextureCache::p_inst = new TextureCache();
            }
            return p_inst;
        }

        void kill(){
            SGE::TextureCache::arc--;
            
            if (SGE::TextureCache::arc == 0){
                //std::cout << ">>    TextureCache singleton deleted" << std::endl;
             
                delete this;
            }
        }
      
        SGE::GLTexture getTexture(const char* _key){
            std::map<std::string, SGE::GLTexture>::iterator mit = this->textureMap.find(std::string(_key));
            if (mit == this->textureMap.end()){
                GLTexture newTexture = SGE::ImageLoader::loadPNG(_key);
                
                this->textureMap.insert(std::make_pair(_key, newTexture));
                
                //std::cout << ">>    Loaded Non-Cache Texture!" << std::endl;

                return newTexture;
            }
            
            //std::cout << ">>    Used Cache Texture!" << std::endl;
            return mit->second;
        }
    };

    int SGE::TextureCache::arc = 0;
    SGE::TextureCache* SGE::TextureCache::p_inst = nullptr;

}

#endif /* sge_texture_cache_h */
