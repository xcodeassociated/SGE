//
//  shader.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 17.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef shader_h
#define shader_h

#include "../include/sge_include.hpp"

namespace SGE {
    
    class Shader{
        GLuint programID = 0, vertexShaderID = 0, fragmentShaderID = 0;
        unsigned short arrtibute_count = 0;
        bool isCompiled = false, isAttributed = false, isLinked = false;
        
        bool compileShader(std::string _filePath, GLuint& _id){
            std::ifstream vertexFile(_filePath);
            if (vertexFile.fail()) throw "";
            
            std::string fileContent;
            std::string line;
            while (std::getline(vertexFile, line)){
                fileContent += line + "\n";
            }vertexFile.close();
            
            const char* contentChar = fileContent.c_str();
            
            glShaderSource(_id, 1, &contentChar, nullptr);
            glCompileShader(_id);
            
            GLint status;
            glGetShaderiv(_id, GL_COMPILE_STATUS, &status);
            if (status == GL_FALSE){
                GLint maxLength = 0;
                glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &maxLength);
                
                std::vector<char> errorLog(maxLength);
                glGetShaderInfoLog(_id, maxLength, &maxLength, &errorLog[0]);
                glDeleteShader(_id);
                std::cout << &(errorLog[0]) << std::endl;
                
                return false;
            }
            return true;
        }

    public:
        Shader(){
        
        };
        
        ~Shader(){
            
        };
        
        GLint getUniformLocation(const char* uniformName){
            GLint location = glGetUniformLocation(this->programID, uniformName);
            if (location == GL_INVALID_INDEX) throw "";
            
            return location;
        }
        
        void doShaders(const char* _vertexShaderFile, const char* _fragmentShaderFile){
        
            this->programID = glCreateProgram();
            
            this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            if (this->vertexShaderID == 0) throw "";
            
            this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
            if (this->fragmentShaderID == 0) throw "";
            
            if (this->compileShader(_vertexShaderFile, this->vertexShaderID) == false ||
                this->compileShader(_fragmentShaderFile, this->fragmentShaderID) == false)
            {
                
                    //throw "shader file faild to compile...";
            }else
                this->isCompiled = true;
            
        }
        
        void addAttribute(const char* attributeName){
            if (this->isCompiled){
                glBindAttribLocation(this->programID, this->arrtibute_count, attributeName);
                this->arrtibute_count++;
                this->isAttributed = true;
            }else throw "";
        }
        
        bool linkShaders(){
            if (this->isCompiled && this->isAttributed){
                glAttachShader(this->programID, this->vertexShaderID);
                glAttachShader(this->programID, this->fragmentShaderID);
                
                glLinkProgram(this->programID);
                
                GLint isLinked = 0;
                glGetProgramiv(this->programID, GL_LINK_STATUS, (int*)&isLinked);
                if (isLinked == GL_FALSE){
                    glDeleteProgram(this->programID);
                    glDeleteShader(this->vertexShaderID);
                    glDeleteShader(this->fragmentShaderID);
                    
                    return false;
                }
                
                glDetachShader(this->programID, this->vertexShaderID);
                glDetachShader(this->programID, this->fragmentShaderID);
                glDeleteShader(this->vertexShaderID);
                glDeleteShader(this->fragmentShaderID);
                
                this->isLinked = true;
                
                return true;
            }else
                return false;
        }
        
        void use(){
            if (this->isCompiled && this->isAttributed && this->isLinked){
                for (int i = 0; i < this->arrtibute_count; i++)
                    glEnableVertexAttribArray(i);
                
                glUseProgram(this->programID);
            }else
                throw "";
        }
        
        void unuse(){
            if (this->isCompiled && this->isAttributed && this->isLinked){
                for (int i = 0; i < this->arrtibute_count; i++)
                    glDisableVertexAttribArray(i);
                
                glUseProgram(0);
            }else
                throw "";
        }


    };
}

#endif /* shader_h */
