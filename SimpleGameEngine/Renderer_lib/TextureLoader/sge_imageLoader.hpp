//
//  sge_imageLoader.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_imageLoader_h
#define sge_imageLoader_h

#include ".sge_include.hpp"
#include "sge_io_manager.hpp"
#include "../ThirdParty_Librarys/PicoPNG/picopng.cpp"

namespace SGE{
    
    struct ImageLoader{
        
        static SGE::GLTexture loadPNG(const char* filePath) {
            GLTexture texture = {0,0,0};
            
            std::vector<unsigned char> in;
            std::vector<unsigned char> out;
            
            unsigned long width, height;
            
            if (SGE::IOManager::readFileToBuffer(filePath, in) == false) {
                throw "Failed to load PNG file to buffer!";
            }
            
            int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
            if (errorCode != 0) {
                throw "decodePNG failed with error: "; // + std::to_string(errorCode));
            }
            
            glGenTextures(1, &(texture.id));
            
            glBindTexture(GL_TEXTURE_2D, texture.id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            
            glGenerateMipmap(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 0);
            
            texture.width = (unsigned int)width;
            texture.height = (unsigned int)height;
            
            return texture;
        }
        
        
    };
}


#endif /* sge_imageLoader_h */
