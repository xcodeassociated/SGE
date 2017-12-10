#ifndef SGE_MACRO
#define SGE_MACRO

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

// Windows specific
#ifdef _WIN32

#define PATH "C:/Dev/SGE/" // TODO: has to be changed!

#endif

// !Windows specific includes
#ifdef __APPLE__

#define PATH "/Users/Hamashy/Documents/Development/SGE/" // TODO: has to be changed!

#endif

#ifdef __linux

#define PATH "/home/hamashy/Desktop/SGE/" // TODO:  has to be changed!

#endif

#define FRAG PATH "SimpleGameEngine/Renderer_lib/Shaders/res/colorShader.frag"
#define VERT PATH "SimpleGameEngine/Renderer_lib/Shaders/res/colorShader.vert"

#endif /* SGE_MACRO */
