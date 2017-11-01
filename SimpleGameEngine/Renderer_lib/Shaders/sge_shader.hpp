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
    
	/**
     * \brief 
     */
    class Shader{
	    /**
	     * \brief 
	     */
	    GLuint programID = 0;
	    /**
	     * \brief 
	     */
	    GLuint vertexShaderID = 0;
	    /**
	     * \brief 
	     */
	    GLuint fragmentShaderID = 0;
	    /**
	     * \brief 
	     */
	    unsigned short arrtibute_count = 0;
	    /**
	     * \brief 
	     */
	    bool isCompiled = false;
	    /**
	     * \brief 
	     */
	    bool isAttributed = false;
	    /**
	     * \brief 
	     */
	    bool isLinked = false;

	    /**
	     * \brief 
	     * \param _filePath 
	     * \param _id 
	     * \return 
	     */
	    bool compileShader(std::string _filePath, GLuint& _id);

    public:
	    /**
	     * \brief 
	     */
	    Shader();

	    /**
	     * \brief 
	     */
	    ~Shader();

	    /**
	     * \brief 
	     * \param uniformName 
	     * \return 
	     */
	    GLint getUniformLocation(const char* uniformName);

	    /**
	     * \brief 
	     * \param _vertexShaderFile 
	     * \param _fragmentShaderFile 
	     */
	    void doShaders(const char* _vertexShaderFile, const char* _fragmentShaderFile);

	    /**
	     * \brief 
	     * \param attributeName 
	     */
	    void addAttribute(const char* attributeName);

	    /**
	     * \brief 
	     * \return 
	     */
	    bool linkShaders();

	    /**
	     * \brief 
	     */
	    void use();

	    /**
	     * \brief 
	     */
	    void unuse();
    };
}

#endif /* shader_h */
