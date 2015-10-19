//
//  SGE_include.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 16.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef SGE_include_h
#define SGE_include_h

#include <GL/glew.h>
#ifdef WIN32 //Windows specific includes
#include <GL\glut.h>
#else
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#endif
#include <SDL2/SDL.h>

#include <functional>
#include <memory>
#include <chrono>
#include <thread>
#include <algorithm> // MSVC requires explicit inclusion for for_each

#include <string>

#include <vector>
#include <map>
#include <tuple>

#include <fstream>
#include <iostream>

#include <cstdlib>
#include <cstddef>

#endif /* SGE_include_h */
