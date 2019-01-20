//
//  sge_imageLoader.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_imageLoader_h
#define sge_imageLoader_h

#include "../../Sprite/Texture/sge_texture.hpp"

#include <vector>

namespace SGE
{
    struct ImageLoader
	{
	    static SGE::GLTexture loadPNG(const char* filePath);
        static bool readFileToBuffer(const char* filePath, std::vector<unsigned char>& buffer);
    };
}


#endif /* sge_imageLoader_h */
