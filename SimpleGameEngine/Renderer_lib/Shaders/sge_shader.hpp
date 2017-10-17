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

namespace SGE {
    
    class Shader{
        GLuint programID = 0, vertexShaderID = 0, fragmentShaderID = 0;
        unsigned short arrtibute_count = 0;
        bool isCompiled = false, isAttributed = false, isLinked = false;

	    bool compileShader(std::string _filePath, GLuint& _id);

    public:
	    Shader();;

	    ~Shader();;

	    GLint getUniformLocation(const char* uniformName);

	    void doShaders(const char* _vertexShaderFile, const char* _fragmentShaderFile);

	    void addAttribute(const char* attributeName);

	    bool linkShaders();

	    void use();

	    void unuse();
    };
}

#endif /* shader_h */