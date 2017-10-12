//
//  sge_io.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_io_h
#define sge_io_h

#include "sge_include.hpp"

namespace SGE {
    
    struct IOManager{
        
       static bool readFileToBuffer(const char* filePath, std::vector<unsigned char>& buffer) {
            std::ifstream file(filePath, std::ios::binary);
            if (file.fail()) {
                //perror(filePath.c_str());
                return false;
            }
            
            //seek to the end
            file.seekg(0, std::ios::end);
            
            //Get the file size
            int fileSize = file.tellg();
            file.seekg(0, std::ios::beg);
            
            //Reduce the file size by any header bytes that might be present
            fileSize -= file.tellg();
            
            buffer.resize(fileSize);
            file.read((char*)&(buffer[0]), fileSize);
            file.close();
            
            return true;
        }
    };
    
}

#endif /* sge_io_h */
