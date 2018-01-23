#include "sge_game.hpp"
#include "sge_director.hpp"
#include "sge_input_binder.hpp"
#include "sge_mouse.hpp"
#include "sge_object.hpp"
#include "sge_camera2d.hpp"
#include "sge_logic.hpp"
#include "sge_scene.hpp"
#include "sge_camera_handler.hpp"
#include "sge_renderer.hpp"
#include "sge_window_manager.hpp"
#include "sge_fps_limiter.hpp"
#include "sge_input_handler.hpp"
#include "sge_resource_manager.hpp"
#include "sge_action.hpp"
#include "sge_scene_state.hpp"

std::shared_ptr<SGE::Logger> SGE::Game::logger = SGE::LoggerFactory::create_logger("Game");
std::shared_ptr<SGE::LoggerError> SGE::Game::logger_err = SGE::LoggerFactory::create_logger_error("Game_ERROR");

bool SGE::Game::init(float fps)
{
	std::pair<int, int> resolution = this->director->getResolution();

	this->limiter = new FpsLimiter;
	this->limiter->init(fps);
	this->window_manager = new WindowManager(resolution);
	this->window_manager->createWindow();

	this->camera_handler = new CameraHandler(resolution);
	this->camera_handler->setPosition(this->camera_handler->getScreenToWorld(0, 0));
	this->camera_handler->setScale(.5f);

	this->renderer = new Renderer(resolution, this->window_manager, this->camera_handler, this->resourceManager);

	this->input_handler = new InputHandler(this);
    this->action_handler = new ActionHandler();

	return true;
}

bool SGE::Game::isOnScene() const
{
	return this->OnScene;
}

void SGE::Game::run()
{
	//TODO: this should be executed before - required if we want to swap scene
	this->renderer->initShader();
	this->renderer->spriteBatchInit();
	//TODO delay it a bit more
	this->running = true;
	while(this->running)
	{	
		this->currentScene = director->getNextScene();
		this->action_handler->setActions(this->currentScene->getActions());
		if(this->currentScene->state != SceneState::Ready)
		{
			this->director->loadScene(this->currentScene);
		}
		//Do something with renderer
		if(this->window_manager->isHidden())
		{
			this->window_manager->showWindow();
		}
		this->OnScene = true;
		this->currentScene->onDraw();
		this->currentScene->state = SceneState::Playing;
		this->loop();
		this->currentScene->state = SceneState::Ready;
	}
}

SGE::Camera2d* SGE::Game::getCamera()
{
	return this->camera_handler->getCamera();
}

SGE::Game* SGE::Game::getGame()
{
	static Game* game = new Game();
	return game;
}

void SGE::Game::mapAction(const SGE::InputBinder& bind)
{
	this->input_handler->mapAction(bind);
}

void SGE::Game::unmapAction(const SGE::InputBinder& bind)
{
	this->input_handler->unmapAction(bind);
}

void SGE::Game::finalize()
{
	this->input_handler->clear();
	*logger << "Game Finalize method invoked" << std::endl;
}

void SGE::Game::windowClosing()
{
	this->window_manager->finalizeWindow();
	this->stop();
}

SGE::ActionHandler* SGE::Game::getActionHandler()
{
	return this->action_handler;
}

SGE::MouseObject* SGE::Game::getMouse()
{
	return this->input_handler->getMouseHandler()->getMouseObject();
}

void SGE::Game::bindDirector(SGE::Director* director)
{
	this->director = director;
	director->bindGame(this);
}

SGE::Game::Game() : resourceManager(SGE::ResourceManager::getSingleton())
{
}

void SGE::Game::loop()
{
	Logic::action_handler = this->action_handler;
	this->playing = true;
	this->limiter->reset();
	while (this->playing)
	{
		this->limiter->begin();
		{
			this->input_handler->pollEvents();
			this->performLogics();
			this->performActions();
			this->draw(this->currentScene);
		}
		this->fps = this->limiter->end();

		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 100) {
			frameCounter = 0;
			*logger << "fps: " << this->fps << std::endl;
			*logger << "delta_time: " << delta_time << std::endl;
		}
	}
}

void SGE::Game::performActions()
{
	auto& actions = this->currentScene->getActions();
	auto last = std::remove_if(actions.begin(),actions.end(), [](Action*const action)
	{
		action->action_main();
		if (!action->isActive())
		{
			action->action_ends();
			// release object locks
			auto objects = action->getObjects();
			if (objects)
			{
				for (auto object : *objects)
				{
					object->setLock(LogicPriority::None);
				}
			}
			delete action;
			return true;
		}
		return false;
	});
	actions.erase(last,actions.end());
}

void SGE::Game::performLogics()
{
	auto& lVec = this->currentScene->getLogics();

//	LogicPriority objectCurrentLogicP = LogicPriority::None;
//	LogicPriority nextLogicP = LogicPriority::None;

	for(auto logic : lVec)
	{
		//nextLogicP = (*it)->getPriority();
		//if (nextLogicP <= objectCurrentLogicP)
		{
			if(logic->getOn())
				logic->performLogic();
		}
	}
}

void SGE::Game::stop()
{
	this->running = this->playing = false;
}

void SGE::Game::draw(SGE::Scene* scene)
{
	this->renderer->render(scene);
}

SGE::Object* SGE::Game::textureObject(SGE::Object *object, std::string path)
{
	// TODO: Check if file exists!

	if (!path.empty())
	{
		object->texture = this->resourceManager->getTexture(path.c_str());
		object->hasTexture = true;
	}
	else
		throw std::runtime_error{"Object texture path string empty"};

	return object;
}
