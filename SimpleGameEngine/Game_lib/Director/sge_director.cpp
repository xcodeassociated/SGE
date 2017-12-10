#include "sge_director.hpp"
#include "sge_object_manager.hpp"
#include "sge_logic_bind.hpp"
#include <algorithm>
#include <iostream>

std::shared_ptr<SGE::Logger> SGE::Director::logger = LoggerFactory::create_logger("Director");
std::shared_ptr<SGE::LoggerError> SGE::Director::logger_err = LoggerFactory::create_logger_error("Director_ERROR");

SGE::Director::Director(int w, int h): Width(w), Height(h)
{
}

SGE::Director::~Director()
{
}

SGE::Director* SGE::Director::getDirector(int w, int h)
{
	static Director* director = new Director(w, h);
	return director;
}

std::pair<int, int> SGE::Director::getResolution()
{
	return std::make_pair(this->Width, this->Height);
}

SGE::Scene* SGE::Director::addScene(Scene* scene)
{
	this->scenes.push_back(scene);
	manager->addScene(scene);
	return scene;
}

void SGE::Director::deleteScene(Scene* scene)
{
	auto sceneIt = std::find(this->scenes.begin(), this->scenes.end(), scene);
	if (sceneIt != this->scenes.end())
	{
		this->scenes.erase(sceneIt);
		this->manager->deleteScene(scene);
	}
}

void SGE::Director::addLogicBinder(Scene* scene, Logic::Binder logic)
{
	scene->getLogics().push_back(logic);
	std::stable_sort(scene->getLogics().begin(), scene->getLogics().end());
}

void SGE::Director::addLogicBinder(Scene* scene, Object* obj, Logic* logic)
{
	this->addLogicBinder(scene, Logic::Binder(logic, obj));
}

void SGE::Director::unbindLogic(Scene* scene, Object* obj, Logic* logic)
{
	auto it = std::find(scene->getLogics().begin(), scene->getLogics().end(), Logic::Binder(logic, obj));
	if (it == scene->getLogics().end()) 
		return;
	scene->getLogics().erase(it);
}

void SGE::Director::showScene(Scene* scene)
{
	if (!scene->TextureLoaded)
	{
		throw std::runtime_error("Scene texture not loaded");
	}
	this->manager->showScene(scene);
}

void SGE::Director::swapScene(Scene* scene)
{
	if (!scene->TextureLoaded)
	{
		throw std::runtime_error("Scene texture not loaded");
	}
	this->manager->swapScene(scene);
}

void SGE::Director::finalize()
{
	*logger << "Director Finalize method invoked" << std::endl;
}

void SGE::Director::bindManager(ObjectManager* objectManager)
{
	this->manager = objectManager;
}
