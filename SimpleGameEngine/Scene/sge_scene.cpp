#include "sge_scene.hpp"
#include "../Level/LevelParser/sge_level_parser.hpp"
#include <stdexcept>
#include <algorithm>

SGE::Scene::LogicVector& SGE::Scene::getLogics()
{
	return this->logics;
}

SGE::Scene::ActionVector& SGE::Scene::getActions()
{
	return this->actions;
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
	this->objects.emplace_back(object);
}

void SGE::Scene::removeObject(SGE::Object* object)
{
	auto it = std::find(this->objects.begin(), this->objects.end(), object);
	if (it == this->objects.end())
		throw std::runtime_error{"Object not found -- cannot be removed"};

	this->objects.erase(std::remove(this->objects.begin(), this->objects.end(), *it), this->objects.end());
}

void SGE::Scene::addLogic(SGE::Logic* logic)
{
	this->logics.push_back(logic);
	std::stable_sort(this->logics.begin(), this->logics.end(), [](Logic* lhs, Logic* rhs)->bool { return lhs->getPriority() < rhs->getPriority(); });
}

void SGE::Scene::removeLogic(SGE::Logic* logic)
{
	auto it = std::find(this->logics.begin(), this->logics.end(), logic);
	if (it == this->logics.end())
		throw std::runtime_error{"Could not find LogicBinder to remove from Scene"};

	this->logics.erase(std::remove(this->logics.begin(), this->logics.end(), logic), this->logics.end());
}

void SGE::Scene::addAction(Action* action)
{
	this->actions.push_back(action);
}

void SGE::Scene::removeAction(Action* action)
{
	auto it = std::find(this->actions.begin(), this->actions.end(), action);
	if (it == this->actions.end())
		throw std::runtime_error{"Could not find Action to remove from Scene"};

	this->actions.erase(std::remove(this->actions.begin(), this->actions.end(), action), this->actions.end());
}

void SGE::Scene::loadScene()
{
}

void SGE::Scene::suspendScene()
{
}

void SGE::Scene::resumeScene()
{
}

void SGE::Scene::unloadScene()
{
}
