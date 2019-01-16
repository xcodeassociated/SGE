//
//  shader.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 17.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef shader_h
#define shader_h

#include <string>
#include <GL/glew.h>

namespace SGE
{
    class Shader
	{
	    GLuint programID = 0;
	    GLuint vertexShaderID = 0;
	    GLuint fragmentShaderID = 0;

	    unsigned short arrtibute_count = 0;

	    bool isCompiled = false;
	    bool isAttributed = false;
	    bool isLinked = false;

	    bool compileShader(std::string _filePath, GLuint& _id);

    public:
	    GLint getUniformLocation(const char* uniformName);

	    void doShaders(const char* _vertexShaderFile, const char* _fragmentShaderFile);
	    bool linkShaders();

	    void addAttribute(const char* attributeName);

	    void use();
	    void unuse();
    };
}

#endif /* shader_h */
