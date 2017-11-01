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

namespace SGE {

	/**
     * \brief Stores key states
     * \todo We wrapped around SDL2 keyboard state. I don't think this is needed.
     */
    class InputManager{
	    /**
         * \brief 
         */
        std::unordered_map<unsigned int, bool> keyMap;
        
    public:
	    /**
		 * \brief 
		 */
		InputManager();
	    /**
	     * \brief 
	     */
	    ~InputManager();

	    /**
	     * \brief 
	     * \param _keyID 
	     */
	    void pressKey(unsigned int _keyID);

	    /**
	     * \brief 
	     * \param _keyID 
	     */
	    void releaseKey(unsigned int _keyID);

	    /**
	     * \brief 
	     * \param _keyID 
	     * \return 
	     */
	    bool isKeyPressed(unsigned int _keyID);
    };

}

#endif
