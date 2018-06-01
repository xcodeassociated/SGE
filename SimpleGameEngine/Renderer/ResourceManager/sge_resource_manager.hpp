//
//  sge_resource_manager.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_resource_manager_h
#define sge_resource_manager_h

#include "../TextureCache/sge_texture_cache.hpp"


namespace SGE
{

    class ResourceManager
	{
        SGE::TextureCache* textureCache = nullptr;
  
        static ResourceManager* p_inst;

        static int arc;

	    ResourceManager() = default;

	    ResourceManager(const ResourceManager&);

    public:
	    static ResourceManager* getSingleton();

	    void kill();

	    SGE::GLTexture getTexture(const char* texture);
    };
    
}

#endif /* sge_resource_manager_h */
