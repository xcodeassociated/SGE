#include "sge_image_loader.hpp"
#include "../../PicoPNG/picopng.h"
#include "../../Sprite/Texture/sge_texture.hpp"

#include <stdexcept>
#include <sstream>
#include <fstream>

SGE::GLTexture SGE::ImageLoader::loadPNG(const char* filePath)
{
	GLTexture texture = {0,0,0};

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;

	unsigned long width, height;

	if (readFileToBuffer(filePath, in) == false)
	{
		std::stringstream msg;
		msg << "Failed to load PNG file to buffer! " << filePath;
		throw std::runtime_error{msg.str()};
	}

	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (errorCode != 0)
	{
		throw std::runtime_error{"decodePNG failed with error: "};
	}

	glGenTextures(1, &(texture.id));

	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = (unsigned int)width;
	texture.height = (unsigned int)height;

	return texture;
}

bool SGE::ImageLoader::readFileToBuffer(const char* filePath, std::vector<unsigned char>& buffer)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail())
	{
		return false;
	}

	file.seekg(0, std::ios::end);

	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char*)&(buffer[0]), fileSize);
	file.close();

	return true;
}
