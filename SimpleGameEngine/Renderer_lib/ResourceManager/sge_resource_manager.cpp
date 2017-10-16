#include "sge_resource_manager.hpp"

int SGE::ResourceManager::arc = 0;
SGE::ResourceManager* SGE::ResourceManager::p_inst = nullptr;

SGE::ResourceManager::ResourceManager(): textureCache(SGE::TextureCache::getSingleton())
{
	//std::cout << ">>    ResourceManager c-tor" << std::endl;
}

SGE::ResourceManager::ResourceManager(const ResourceManager&): textureCache(SGE::TextureCache::getSingleton())
{
	//std::cout << ">>    ResourceManager c-tor" << std::endl;
}

SGE::ResourceManager::~ResourceManager()
{
	this->textureCache->kill();
	this->textureCache = nullptr;
	SGE::ResourceManager::p_inst = nullptr;
}

SGE::ResourceManager* SGE::ResourceManager::getSingleton()
{
	SGE::ResourceManager::arc++;

	if (!p_inst)
	{
		ResourceManager::p_inst = new ResourceManager();
	}
	return p_inst;
}

void SGE::ResourceManager::kill()
{
	SGE::ResourceManager::arc--;

	if (SGE::ResourceManager::arc == 0)
	{
		//std::cout << ">>    ResourceManager singleton deleted!" << std::endl;

		delete this;
	}
}

SGE::GLTexture SGE::ResourceManager::getTexture(const char* texture)
{
	return this->textureCache->getTexture(texture);
}
