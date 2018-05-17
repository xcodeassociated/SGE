#include <algorithm>
#include <iostream>

#include "sge_director.hpp"
#include "../sge_game.hpp"

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
	return scene;
}

void SGE::Director::deleteScene(Scene* scene)
{
	auto sceneIt = std::find(this->scenes.begin(), this->scenes.end(), scene);
	if (sceneIt != this->scenes.end())
	{
		this->scenes.erase(std::remove(this->scenes.begin(), this->scenes.end(), *sceneIt), this->scenes.end());
	}
}

void SGE::Director::finalize()
{
	*logger << "Director Finalize method invoked" << std::endl;
}

void SGE::Director::bindGame(Game* game)
{
	this->game = game;
}

SGE::Scene* SGE::Director::getNextScene()
{
	Scene* next = this->nextScene;
	this->nextScene = nullptr;
	return next;
}

void SGE::Director::setNextScene(Scene* next)
{
	this->nextScene = next;
}

void SGE::Director::loadScene(Scene* scene)
{
	switch(scene->state)
	{
	case SceneState::Standby:
		scene->loadScene();
		break;
	case SceneState::Suspended:
		scene->resumeScene();
		break;
	case SceneState::Ready:
		break;
	default:
		throw std::runtime_error("Cannot load Scene ID:" + std::to_string(scene->id) + " State:" + toString(scene->state));
	}
	scene->state = SceneState::Ready;
}

void SGE::Director::unloadScene(Scene* scene)
{
	switch (scene->state)
	{
	case SceneState::Ready:
	case SceneState::Suspended:
		scene->unloadScene();
		break;
	case SceneState::Standby:
		break;
	default:
		throw std::runtime_error("Cannot prepare Scene ID:" + std::to_string(scene->id) + " State:" + toString(scene->state));
	}
	scene->state = SceneState::Standby;
}

void SGE::Director::resumeScene(Scene* scene)
{
	switch (scene->state)
	{
	case SceneState::Suspended:
		scene->resumeScene();
		break;
	case SceneState::Ready:
		break;
	default:
		throw std::runtime_error("Cannot resume Scene ID:" + std::to_string(scene->id) + " State:" + toString(scene->state));
	}
	scene->state = SceneState::Ready;
}

void SGE::Director::suspendScene(Scene* scene)
{
	switch (scene->state)
	{
	case SceneState::Ready:
		scene->suspendScene();
		break;
	case SceneState::Suspended:
		break;
	default:
		throw std::runtime_error("Cannot resume Scene ID:" + std::to_string(scene->id) + " State:" + toString(scene->state));
	}
	scene->state = SceneState::Suspended;

}

void SGE::Director::toNextScene(Scene* scene)
{
	this->nextScene = scene;
	this->game->playing = false;
}
