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
    
	/**
     * \brief 
     */
    class ResourceManager
	{
	    /**
         * \brief 
         */
        SGE::TextureCache* textureCache = nullptr;
    
	    /**
         * \brief 
         */
        static ResourceManager* p_inst;
	    /**
         * \brief 
         */
        static int arc;

	    /**
	     * \brief 
	     */
	    ResourceManager();
	    /**
	     * \brief 
	     */
	    ResourceManager(const ResourceManager&);

	    /**
	     * \brief 
	     */
	    ~ResourceManager();

    public:
	    /**
	     * \brief 
	     * \return 
	     */
	    static ResourceManager* getSingleton();

	    /**
	     * \brief 
	     */
	    void kill();

	    /**
	     * \brief 
	     * \param texture 
	     * \return 
	     */
	    SGE::GLTexture getTexture(const char* texture);
    };
    
}

#endif /* sge_resource_manager_h */
