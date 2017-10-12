//
//  SGE_include.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 16.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef SGE_include_h
#define SGE_include_h

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

// Windows specific includes
#ifdef _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <SDL2/SDL.h>

#define PATH "C:/Dev/SGE/" // TODO: has to be changed!

#endif

// !Windows specific includes
#ifndef _WIN32
#include <GL/glew.h>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL.h>

#define PATH "/Users/Hamashy/Documents/Development/GameEngine.repo/" // TODO: has to be changed!

//#define FRAG "/Users/Hamashy/Documents/Development/GameEngine.repo/SimpleGameEngine/SGE/Shaders/res/colorShader.frag"
//#define VERT "/Users/Hamashy/Documents/Development/GameEngine.repo/SimpleGameEngine/SGE/Shaders/res/colorShader.vert"

#endif

#define FRAG PATH "SimpleGameEngine/SGE/Shaders/res/colorShader.frag"
#define VERT PATH "SimpleGameEngine/SGE/Shaders/res/colorShader.vert"

//GLM - Math GL library
//#include "../ThirdParty_Librarys/glm/glm.hpp"
//#include "../ThirdParty_Librarys/glm/mat4x4.hpp"
//#include "../ThirdParty_Librarys/glm/gtc/matrix_transform.hpp"
//#include "../ThirdParty_Librarys/glm/gtx/transform.hpp"
//#include "../ThirdParty_Librarys/glm/gtx/rotate_vector.hpp"

#include <functional>
#include <memory>
#include <algorithm>
#include <stdexcept>

#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <initializer_list>

//stream
#include <fstream>
#include <iostream>
#include <sstream>

//c libs
#include <cstdlib>
#include <cstddef>

/** Boost includes: **/
#include <boost/version.hpp>

/** WebSocketpp includes: **/
#ifdef _WIN32 //VS 2015 compatibility fix
#define _WEBSOCKETPP_NOEXCEPT_ 1
#define _WEBSOCKETPP_CPP11_CHRONO_ 1 
#endif
#include <websocketpp/version.hpp>

/** RapidJSON includes: **/
#include <rapidjson/rapidjson.h>

#endif /* SGE_include_h */
