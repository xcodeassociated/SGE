//
//  SGE_include.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 16.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef SGE_include_h
#define SGE_include_h

// Windows specific includes
#ifdef WIN32
#include <GL\glew.h>
#include <GL\glut.h>
#include <SDL2\SDL.h>
#endif

// !Windows specific includes
#ifndef WIN32
#include <GL/glew.h>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL.h>
#endif

//std utils
#include <functional>
#include <memory>
#include <chrono>
#include <thread>
#include <algorithm> 

//string
#include <string>

//std containers
#include <vector>
#include <map>
#include <tuple>

//stream
#include <fstream>
#include <iostream>

//c libs
#include <cstdlib>
#include <cstddef>

/** Boost includes: **/
#include <boost/version.hpp>

/** WebSocketpp includes: **/
#include <websocketpp/version.hpp>

/** RapidJSON includes: **/
#include <rapidjson/rapidjson.h>

/** and.. final let's include "sio" - Socket.IO C++ client **/
#include "../ThirdParty_Librarys/Socket_io-cpp-client/src/sio_client.h"

#endif /* SGE_include_h */
