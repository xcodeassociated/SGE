//
//  sge_imput_manager.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 12.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_imput_manager_h
#define sge_imput_manager_h

#include <unordered_map>

namespace SGE
{
    class InputManager
	{
        std::unordered_map<unsigned int, bool> keyMap;
        
    public:

	    void pressKey(unsigned int _keyID);

	    void releaseKey(unsigned int _keyID);

	    bool isKeyPressed(unsigned int _keyID);
    };

}

#endif
