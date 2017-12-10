#include "sge_scene.hpp"
#include "sge_level_parser.hpp"
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

void SGE::Scene::bindLogic(const SGE::Logic::Binder& logic)
{
	this->Logics.push_back(logic);
	std::stable_sort(this->Logics.begin(), this->Logics.end());
}

void SGE::Scene::bindLogic(SGE::Object* obj, SGE::Logic* logic)
{
	this->bindLogic(Logic::Binder(logic, obj));
}

void SGE::Scene::unbindLogic(SGE::Object* obj, SGE::Logic* logic)
{
	this->unbindLogic(Logic::Binder(logic, obj));
}

void SGE::Scene::unbindLogic(const SGE::Logic::Binder& logic)
{
	auto it = std::find(this->Logics.begin(), this->Logics.end(), logic);
	if (it == this->Logics.end())
		throw std::runtime_error{"Could not find LogicBinder to unbind in Scene"};

	this->Logics.erase(std::remove(this->Logics.begin(), this->Logics.end(), logic), this->Logics.end());
}