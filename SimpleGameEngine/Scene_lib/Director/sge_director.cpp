#include "sge_director.hpp"

SGE::Director::Director(int w, int h): relay(SGE::Relay::getRelay()), Width(w), Height(h)
{
	this->relay->registerDirector(this);
}

SGE::Director::~Director()
{
}

SGE::Director* SGE::Director::getDirector(int w, int h)
{
	static Director* director = new Director(w, h);
	return director; //Can convert to ARC later.
}

std::pair<int, int> SGE::Director::getResolution()
{
	return std::make_pair(this->Width, this->Height);
}

SGE::Scene::ID SGE::Director::addScene(Scene* scene)
{
	SceneID id(relay->getNextCounter(), scene);
	this->scenes.push_back(id);
	relay->relayScene(id);
	return id;
}

void SGE::Director::deleteScene(Scene::ID scene)
{
	auto sceneIt = std::find(this->scenes.begin(), this->scenes.end(), scene);
	if (sceneIt != this->scenes.end())
	{
		this->scenes.erase(sceneIt);
		this->relay->relayDeleteScene(scene);
	}
}

void SGE::Director::addLogicBinder(Scene::ID scene, Logic::Binder logic)
{
	scene.scene->getLogics().push_back(logic);
	std::stable_sort(scene.scene->getLogics().begin(), scene.scene->getLogics().end());
}

void SGE::Director::addLogicBinder(Scene::ID scene, Object::ID obj, Logic::ID logic)
{
	this->addLogicBinder(scene, Logic::Binder(logic, obj));
}

void SGE::Director::unbindLogic(Scene::ID scene, Object::ID obj, Logic::ID logic)
{
	auto it = std::find(scene.scene->getLogics().begin(), scene.scene->getLogics().end(), Logic::Binder(logic, obj));
	if (it == scene.scene->getLogics().end()) return;
	scene.scene->getLogics().erase(it);
}

void SGE::Director::showScene(Scene::ID scene)
{
	if (!scene.scene->TextureLoaded)
	{
		throw std::runtime_error("You are an idiot");
	}
	this->relay->relayShowScene(scene);
}

void SGE::Director::swapScene(Scene::ID scene)
{
	if (!scene.scene->TextureLoaded)
	{
		throw std::runtime_error("You are an idiot");
	}
	this->relay->relaySwapScene(scene);
}

void SGE::Director::finalize()
{
}
