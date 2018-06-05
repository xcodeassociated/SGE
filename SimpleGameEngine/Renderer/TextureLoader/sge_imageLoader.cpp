#include "sge_imageLoader.hpp"
#include "../../PicoPNG/picopng.h"
#include "../IOManager/sge_io_manager.hpp"
#include "../../Sprite/Texture/sge_texture.hpp"

#include <stdexcept>
#include <sstream>

SGE::GLTexture SGE::ImageLoader::loadPNG(const char* filePath)
{
	GLTexture texture = {0,0,0};

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;

	unsigned long width, height;

	if (SGE::IOManager::readFileToBuffer(filePath, in) == false)
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
