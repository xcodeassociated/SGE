#include "sge_camera_handler.hpp"
#include "sge_utils.hpp"
#include <iostream>

namespace SGE {

	ObjectManager::CameraHandler::CameraHandler(std::pair<int, int> resolution, ObjectManager* m) noexcept : manager(m) {
		this->camera = new Camera2d(resolution.first, resolution.second);
		//        this->manager->registerCamera(this->camera);
	}

	Camera2d* ObjectManager::CameraHandler::getCamera()
	{
		return this->camera;
	}

	//should be float or change scale to duble
	void ObjectManager::CameraHandler::setScale(double _scale) noexcept {
		this->camera->setScale(_scale);
	}

	void ObjectManager::CameraHandler::setPosition(int _x, int _y) noexcept {
		this->camera->setPosition(glm::vec2(_x, _y));
	}

	void ObjectManager::CameraHandler::updateCamera(void) const noexcept {
		this->camera->update();
	}

	const glm::mat4& ObjectManager::CameraHandler::getCameraMatrix(void) const noexcept {
		return this->camera->getCameraMatrix();
	}

	void ObjectManager::CameraHandler::setPosition(glm::vec2 pos) noexcept {
		this->setPosition(pos.x, pos.y);
	}

	glm::vec2 ObjectManager::CameraHandler::getScreenToWorld(glm::vec2 pos) const noexcept {
		return SGE::screenToWorld(pos, this->camera->getPosition(), (double)this->camera->getScale()); //this->camera->screenToWorld(pos);
	}

	glm::vec2 ObjectManager::CameraHandler::getScreenToWorld(int _x, int _y) const noexcept {
		return this->getScreenToWorld({ _x, _y });
	}

	ObjectManager::ObjectManager() noexcept: action_handler(new ActionHandler)
	{
		Logic::action_handler = this->action_handler;
		this->relay = Relay::getRelay();
		this->relay->registerManager(this);
	}

	bool ObjectManager::init()
	{
		std::pair<int, int> resolution = this->relay->relayGetResolution();

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
		/*	if(this->renderer == nullptr)
			{
				this->init();
			}*/
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
		//TODO
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

	Action::ID ObjectManager::addAction(Action* action)
	{
		return ActionID(this->counter++, action);
	}

	Logic::ID ObjectManager::addLogic(Logic* logic)
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

	Object::ID ObjectManager::addObject(Object* o, std::string path)
	{
		ObjectID id(counter++, o);
		this->objects.emplace_back(id);

		if (!path.empty()) o->texture = this->rManager->getTexture(path.c_str());

		return id;
	}

	Object::ID ObjectManager::addObject(Object* o, Scene::ID s, std::string path)
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
			throw std::runtime_error("Scene does not exist"); //Todo: replace
		}

		if (!path.empty()) o->texture = this->rManager->getTexture(path.c_str());

		return id;
	}

	void ObjectManager::bindObject(Object::ID o, Scene::ID s)
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

	void ObjectManager::unbindObject(Object::ID o, Scene::ID s)
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
		/* Handle window close action... */
		std::cerr << "SDL Window is trying to close!" << std::endl;
	}

	ActionHandler* ObjectManager::getActionHandler()
	{
		return this->action_handler;
	}

	Object::ID ObjectManager::getCameraID()
	{
		return ObjectID(0, this->camera_handler->getCamera());
	}

	Object::ID ObjectManager::getMouse()
	{
		return ObjectID(1, this->input_handler->getMouseHandler()->getMouseObject());
	}
}
