#include "sge_scene.hpp"
#include "sge_logic_bind.hpp"
#include <sge_level_parser.hpp>
#include <stdexcept>
#include <algorithm>

SGE::Scene::LogicVector& SGE::Scene::getLogics()
{
	return this->Logics;
}

void SGE::Scene::loadLevel(const char* path, std::map<char, std::string> levelMask)
{
	LevelParser parser(path, levelMask);
	this->level = parser.parse();
	this->TextureLoaded = true;
}

SGE::Level& SGE::Scene::getLevel()
{
	return this->level;
}

SGE::Scene::ObjectVector& SGE::Scene::getObjects()
{
	return this->objects;
}

void SGE::Scene::addObject(SGE::Object* object)
{
	if (!object->hasTexture)
		throw std::runtime_error{"Object missing texture"};

	this->objects.emplace_back(object);
}

void SGE::Scene::removeObject(SGE::Object* object)
{
	auto it = std::find(this->objects.begin(), this->objects.end(), object);
	if (it == this->objects.end())
		throw std::runtime_error{"Object not found -- cannot be removed"};

	this->objects.erase(std::remove(this->objects.begin(), this->objects.end(), *it), this->objects.end());
}