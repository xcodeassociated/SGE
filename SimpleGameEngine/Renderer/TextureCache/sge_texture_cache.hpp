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
#include "../../Object/sge_object.hpp"

namespace SGE
{
	/**
     * \brief 
     */
    class TextureCache
	{
        
	    /**
         * \brief 
         */
        std::map<std::string, GLTexture> textureMap;

	    /**
         * \brief 
         */
        static TextureCache* p_inst;
	    /**
         * \brief 
         */
        static int arc;

	    /**
	     * \brief 
	     */
	    TextureCache();

	    /**
	     * \brief 
	     */
	    TextureCache(const TextureCache&);

	    /**
	     * \brief 
	     */
	    ~TextureCache();

    public:
	    /**
	     * \brief 
	     * \return 
	     */
	    static TextureCache* getSingleton();

	    /**
	     * \brief 
	     */
	    void kill();

	    /**
	     * \brief 
	     * \param _key 
	     * \return 
	     */
	    SGE::GLTexture getTexture(const char* _key);
    };

}

#endif /* sge_texture_cache_h */
