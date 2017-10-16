//
//  sge_texture_cache.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_texture_cache_h
#define sge_texture_cache_h

#include <map>
#include "sge_object.hpp"

namespace SGE {

    class TextureCache{
        
        std::map<std::string, GLTexture> textureMap;

        static TextureCache* p_inst;
        static int arc;

	    TextureCache();;

	    TextureCache(const TextureCache&);;

	    ~TextureCache();

    public:
	    static TextureCache* getSingleton();

	    void kill();

	    SGE::GLTexture getTexture(const char* _key);
    };

}

#endif /* sge_texture_cache_h */
