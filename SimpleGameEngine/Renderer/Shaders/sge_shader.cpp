#include "sge_shader.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <stdexcept>

bool SGE::Shader::compileShader(std::string _filePath, GLuint& _id)
{
	std::ifstream vertexFile(_filePath);
	if (vertexFile.fail())
        throw std::runtime_error{"Cannot load shader"};

	std::string fileContent;
	std::string line;
	while (std::getline(vertexFile, line))
	{
		fileContent += line + "\n";
	}
	vertexFile.close();

	const char* contentChar = fileContent.c_str();

	glShaderSource(_id, 1, &contentChar, nullptr);
	glCompileShader(_id);

	GLint status;
	glGetShaderiv(_id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
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

SGE::Shader::Shader()
{
}

SGE::Shader::~Shader()
{
}

GLint SGE::Shader::getUniformLocation(const char* uniformName)
{
	GLint location = glGetUniformLocation(this->programID, uniformName);
	if (location == static_cast<GLint>(GL_INVALID_INDEX))
        throw std::runtime_error{"Cannot get Uniform Location"};
	return location;
}

void SGE::Shader::compileShaders(const char* _vertexShaderFile, const char* _fragmentShaderFile)
{
	this->programID = glCreateProgram();

	this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (this->vertexShaderID == 0)
        throw std::runtime_error{"Cannot create shader"};

	this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (this->fragmentShaderID == 0) throw "";

	if (this->compileShader(_vertexShaderFile, this->vertexShaderID) == false ||
		this->compileShader(_fragmentShaderFile, this->fragmentShaderID) == false)
	{
		throw std::runtime_error{"Shader file filed to compile"};
	}
	else
		this->isCompiled = true;
}

void SGE::Shader::addAttribute(const char* attributeName)
{
	if (this->isCompiled)
	{
		glBindAttribLocation(this->programID, this->arrtibute_count, attributeName);
		this->arrtibute_count++;
		this->isAttributed = true;
	}
	else
        throw std::runtime_error{"Program is not compiled"};
}

bool SGE::Shader::linkShaders()
{
	if (this->isCompiled)
	{
		glAttachShader(this->programID, this->vertexShaderID);
		glAttachShader(this->programID, this->fragmentShaderID);

		glLinkProgram(this->programID);

		GLint isLinked = 0;
		glGetProgramiv(this->programID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
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
	}
	else
		return false;
}

void SGE::Shader::use()
{
	if (this->isCompiled && this->isAttributed && this->isLinked)
	{
		for (int i = 0; i < this->arrtibute_count; i++)
		glEnableVertexAttribArray(i);

		glUseProgram(this->programID);
	}
	else
		throw std::runtime_error{"Cannot use shader program"};
}

void SGE::Shader::unuse()
{
	if (this->isCompiled && this->isAttributed && this->isLinked)
	{
		for (int i = 0; i < this->arrtibute_count; i++)
		glDisableVertexAttribArray(i);

		glUseProgram(0);
	}
	else
		throw std::runtime_error{"Cannot unuse shader program"};
}
