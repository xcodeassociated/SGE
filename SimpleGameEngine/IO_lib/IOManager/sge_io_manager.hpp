//oManager
//  sge_io.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef sge_io_h
#define sge_io_h

#include <vector>


namespace SGE {
    
    struct IOManager{
	    /**
	     * \brief Reads file at given filePath and stores it in the buffer
	     * \param filePath Path to file
	     * \param buffer Buffer used to store file.
	     * \return False if file fails to open, True otherwise.
	     */
	    static bool readFileToBuffer(const char* filePath, std::vector<unsigned char>& buffer);
    };
    
}

#endif /* sge_io_h */
