//
//  sge_glTexture.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_glTexture_h
#define sge_glTexture_h

#include "../include/sge_include.hpp"

namespace SGE{
    
    struct GLTexture {
        GLuint id;
        unsigned int width;
        unsigned int height;
        
        GLTexture(){
            
        }
        ~GLTexture(){
            
        }
    };
    
}

#endif /* sge_glTexture_h */
