#include "sge_texture_cache.hpp"
#include "../TextureLoader/sge_imageLoader.hpp"

#include <string>

int SGE::TextureCache::arc = 0;
SGE::TextureCache* SGE::TextureCache::p_inst = nullptr;

SGE::TextureCache::TextureCache()
{
}

SGE::TextureCache::TextureCache(const TextureCache&)
{
}

SGE::TextureCache::~TextureCache()
{
	SGE::TextureCache::p_inst = nullptr;
}

SGE::TextureCache* SGE::TextureCache::getSingleton()
{
	SGE::TextureCache::arc++;

	if (!p_inst)
	{
		TextureCache::p_inst = new TextureCache();
	}
	return p_inst;
}

void SGE::TextureCache::kill()
{
	SGE::TextureCache::arc--;

	if (SGE::TextureCache::arc == 0)
	{
		delete this;
	}
}

SGE::GLTexture SGE::TextureCache::getTexture(const char* _key)
{
	std::map<std::string, SGE::GLTexture>::iterator mit = this->textureMap.find(std::string(_key));
	if (mit == this->textureMap.end())
	{
		GLTexture newTexture = SGE::ImageLoader::loadPNG(_key);

		this->textureMap.insert(std::make_pair(_key, newTexture));

		return newTexture;
	}

	return mit->second;
}
