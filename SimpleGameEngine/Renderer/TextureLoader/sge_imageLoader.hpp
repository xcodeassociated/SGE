//
//  sge_imageLoader.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_imageLoader_h
#define sge_imageLoader_h

#include "../../Object/sge_object.hpp"

namespace SGE
{
	/**
     * \brief 
     */
    struct ImageLoader
	{
	    /**
	     * \brief 
	     * \param filePath 
	     * \return 
	     */
	    static SGE::GLTexture loadPNG(const char* filePath);
    };
}


#endif /* sge_imageLoader_h */
