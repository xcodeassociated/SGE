#include "sge_object_manager.hpp"
#include "sge_director.hpp"
#include "sge_logic_bind.hpp"
#include "sge_input_binder.hpp"
#include "sge_mouse.hpp"
#include "sge_object.hpp"
#include "sge_camera2d.hpp"
#include "sge_logic.hpp"

#include "tool/sge_camera_handler.hpp"
#include "tool/sge_game.hpp"
#include "tool/sge_input_handler.hpp"
#include "tool/sge_renderer.hpp"
#include "tool/sge_window_manager.hpp"

#include <iostream>

namespace SGE
{
	ObjectManager::ObjectManager() noexcept: action_handler(new ActionHandler)
	{
		Logic::action_handler = this->action_handler;
	}

	bool ObjectManager::init()
	{
		std::pair<int, int> resolution = this->director->getResolution();

		this->window_manager = new WindowManager(resolution, this);
		this->window_manager->createWindow();

		this->camera_handler = new CameraHandler(resolution, this);
		this->camera_handler->setPosition(this->camera_handler->getScreenToWorld(0, 0));
		this->camera_handler->setScale(.5f);

		this->renderer = new Renderer(resolution, this, this->window_manager, this->camera_handler);
		// this->renderer->initShader();
		this->game = new Game(this, this->action_handler);

		this->input_handler = new InputHandler(this);
		this->game->setInputHandler(this->input_handler);
		return true;
	}

	void ObjectManager::addScene(SceneID s)
	{
		static bool init = this->init();
		this->sceneObjects.emplace(s, std::vector<ObjectID>());
	}

	void ObjectManager::deleteScene(SceneID s)
	{
		if (this->sceneObjects.erase(s) != 0)
		{
			s.scene->finalize();
			delete s.scene;
		}
	}

	bool ObjectManager::isOnScene()
	{
		return this->OnScene;
	}

	void ObjectManager::showScene(SceneID s)
	{
		this->currentScene = s.scene;
		auto sceneObjectsIt = this->sceneObjects.find(s);
		if (sceneObjectsIt == this->sceneObjects.end()) throw std::runtime_error("Scene not Loaded");
		s.scene->BindObjects(&sceneObjectsIt->second);

		this->OnScene = true;

		//this->window_manager->createWindow();
		this->window_manager->showWindow();

		this->renderer->initShader();

		this->renderer->spriteBatchInit();

		s.scene->onDraw();

		this->game->run();
	}

	void ObjectManager::swapScene(SceneID s)
	{
	}

	Level& ObjectManager::getSceneData(SceneID s)
	{
		return s.scene->getLevel();
	}

	Camera2d* ObjectManager::getCamera()
	{
		return this->camera_handler->getCamera();
	}

	ObjectManager* ObjectManager::getManager()
	{
		static ObjectManager* manager = new ObjectManager();
		return manager; //Can be converted to ARC later.
	}

	Object* ObjectManager::getObjectPtr(ObjectID id)
	{
		return id.obj;
	}

	Scene* ObjectManager::getScenePtr(SceneID id)
	{
		return id.scene;
	}

	Logic* ObjectManager::getLogicPtr(LogicID id)
	{
		return id.logic;
	}

	void ObjectManager::mapAction(const InputBinder& bind)
	{
		this->input_handler->mapAction(bind);
	}

	void ObjectManager::unmapAction(const InputBinder& bind)
	{
		this->input_handler->unmapAction(bind);
	}

	ActionID ObjectManager::addAction(Action* action)
	{
		return ActionID(this->counter++, action);
	}

	LogicID ObjectManager::addLogic(Logic* logic)
	{
		return LogicID(this->counter++, logic);
	}

	void ObjectManager::interrupt()
	{
		if (this->game)
		{
			this->game->stop();
		}
	}

	ObjectID ObjectManager::addObject(Object* o, std::string path)
	{
		ObjectID id(counter++, o);
		this->objects.emplace_back(id);

		if (!path.empty()) o->texture = this->rManager->getTexture(path.c_str());

		return id;
	}

	ObjectID ObjectManager::addObject(Object* o, SceneID s, std::string path)
	{
		ObjectID id(counter++, o);
		this->objects.emplace_back(id);
		auto ObjectVectorIt = this->sceneObjects.find(s);
		if (ObjectVectorIt != this->sceneObjects.end())
		{
			ObjectVectorIt->second.emplace_back(id);
		}
		else
		{
			throw std::runtime_error("Scene does not exist");
		}

		if (!path.empty()) o->texture = this->rManager->getTexture(path.c_str());

		return id;
	}

	void ObjectManager::bindObject(ObjectID o, SceneID s)
	{
		auto ObjectVectorIt = this->sceneObjects.find(s);
		if (ObjectVectorIt != this->sceneObjects.end())
		{
			ObjectVectorIt->second.emplace_back(o);
		}
		else
		{
			throw std::runtime_error("Scene does not exist");
		}
	}

	void ObjectManager::unbindObject(ObjectID o, SceneID s)
	{
		auto objectVectorIt = this->sceneObjects.find(s);
		if (objectVectorIt != this->sceneObjects.end())
		{
			auto objectIt = std::find(objectVectorIt->second.begin(), objectVectorIt->second.end(), o);
			if (objectIt != objectVectorIt->second.end())
			{
				objectVectorIt->second.erase(objectIt);
			}
		}
	}

	void ObjectManager::update(ObjectID id, const Action& action)
	{
		;
	}

	void ObjectManager::finalize()
	{
		;
	}

	void ObjectManager::windowClosing()
	{
		std::cerr << "SDL Window is trying to close!" << std::endl;
	}

	ActionHandler* ObjectManager::getActionHandler()
	{
		return this->action_handler;
	}

	ObjectID ObjectManager::getCameraID()
	{
		return ObjectID(0, this->camera_handler->getCamera());
	}

	ObjectID ObjectManager::getMouse()
	{
		return ObjectID(1, this->input_handler->getMouseHandler()->getMouseObject());
	}

	void ObjectManager::bindDirector(Director* director)
	{
		this->director = director;
		director->bindManager(this);
	}
}
