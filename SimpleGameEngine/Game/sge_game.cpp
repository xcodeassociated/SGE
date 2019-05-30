#include "sge_game.hpp"
#include "Director/sge_director.hpp"
#include "InputHandler/sge_input_binder.hpp"
#include "../IO/Mouse/sge_mouse.hpp"
#include "../Object/sge_object.hpp"
#include "../Object/Camera2d/sge_camera2d.hpp"
#include "../Logic/sge_logic.hpp"
#include "../Scene/sge_scene.hpp"
#include "../Renderer/CameraHandler/sge_camera_handler.hpp"
#include "../Renderer/sge_renderer.hpp"
#include "../Renderer/WindowManager/sge_window_manager.hpp"
#include "../Utils/Timing/sge_fps_limiter.hpp"
#include "InputHandler/sge_input_handler.hpp"
#include "../Renderer/ResourceManager/sge_resource_manager.hpp"
#include "../Action/sge_action.hpp"
#include "../Scene/sge_scene_state.hpp"

std::shared_ptr<SGE::Logger> SGE::Game::logger = SGE::LoggerFactory::create_logger("Game");
std::shared_ptr<SGE::LoggerError> SGE::Game::logger_err = SGE::LoggerFactory::create_logger_error("Game_ERROR");

bool SGE::Game::init(float fps, const std::string& glslPath)
{
	std::pair<int, int> resolution = this->director->getResolution();

	this->limiter = new FpsLimiter;
	this->limiter->init(fps);
	this->window_manager = new WindowManager(resolution);
	this->window_manager->createWindow();

	this->camera_handler = new CameraHandler(resolution);
	this->camera_handler->setPosition(this->camera_handler->getScreenToWorld({resolution.first, resolution.second}, 0, 0));
	this->camera_handler->setScale(.5f);

	if (glslPath.empty())
		throw std::runtime_error{"glsl path empty"};

	const auto vert = glslPath + "/BatchShader.vert";
	const auto frag = glslPath + "/BatchShader.frag";

	this->renderer = new BatchRenderer(this->camera_handler, this->resourceManager, this->window_manager);

	this->input_handler = new InputHandler(this);
    this->action_handler = new ActionHandler();

	return true;
}

bool SGE::Game::isOnScene() const
{
	return this->OnScene;
}

void SGE::Game::setGamePath(const std::string& path)
{
	if (!path.empty())
		this->game_path = path;
}

void SGE::Game::setShadersPath(const std::string& path)
{
	if(!path.empty())
		this->shader_path = path;
}

const std::string& SGE::Game::getGamePath() const
{
	return this->game_path;
}

const std::string& SGE::Game::getShadersPath() const
{
	return this->shader_path;
}


void SGE::Game::run()
{
	////TODO: this should be executed before - required if we want to swap scene
	//this->renderer->initShader();
	//this->renderer->spriteBatchInit();
	//TODO delay it a bit more
	this->running = true;
	while(this->running)
	{	
		this->currentScene = director->getNextScene();
		this->action_handler->setActions(this->currentScene->getActions());
		if(this->currentScene->state != SceneState::Ready)
		{
			this->renderer->setScene(this->currentScene);
			this->director->loadScene(this->currentScene);
		}
		if(this->window_manager->isHidden())
		{
			this->window_manager->showWindow();
		}
		this->OnScene = true;
		this->renderer->setScene(this->currentScene);
		this->currentScene->onDraw();
		this->currentScene->state = SceneState::Playing;
		this->loop();
		this->currentScene->state = SceneState::Ready;
	}
	this->windowClosing();
}

void SGE::Game::hide() const
{
	this->window_manager->hideWindow();
}

SGE::Camera2d* SGE::Game::getCamera() const
{
	return this->camera_handler->getCamera();
}

SGE::Game* SGE::Game::getGame()
{
	static Game* game = new Game();
	return game;
}

void setGLSLPath(const char* path)
{
	if (path == nullptr)
		throw std::runtime_error{"Empty GLSL path"};


}

void SGE::Game::mapAction(const SGE::InputBinder& bind)
{
	this->input_handler->mapAction(bind);
}

void SGE::Game::unmapAction(const SGE::InputBinder& bind)
{
	this->input_handler->unmapAction(bind);
}

void SGE::Game::unmapAll()
{
	this->input_handler->clear();
}

void SGE::Game::finalize()
{
	SDL_Quit();
	this->input_handler->clear();
	*logger << "Game Finalize method invoked" << std::endl;
}

void SGE::Game::windowClosing()
{
	this->window_manager->finalizeWindow();
	this->stop();
}

void SGE::Game::raiseWindow()
{
	this->window_manager->raiseWindow();
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
			if (!this->playing) return;
			this->performLogics();
			this->performActions();
			this->draw(this->currentScene);
		}
		this->fps = this->limiter->end();
#ifndef NDEBUG
		static float time_counter = 0.f;
		time_counter += delta_time;
		while (time_counter > 60.f)
		{
			*logger << "fps: " << this->fps << std::endl;
			*logger << "delta_time: " << delta_time << std::endl;
			time_counter = 0.f;
		}
#endif
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
	for(auto logic : lVec)
	{
		if(logic->getOn())
		{
			logic->performLogic();
		}
	}
}

void SGE::Game::stop()
{
	this->running = false;
	this->playing = false;
}

void SGE::Game::draw(SGE::Scene* scene)
{
	this->renderer->render(scene);
}

SGE::Object* SGE::Game::textureObject(SGE::Object *object, const std::string& texture_file)
{
	if (!texture_file.empty())
	{
	    std::string file_absolute_path = "";
	    if (texture_file[0] != '/')
        {
        	file_absolute_path = this->game_path + texture_file;
        }else
            file_absolute_path = texture_file;

		object->setTexture(this->resourceManager->getTexture(file_absolute_path.c_str()));
		object->setTextured(true);
	}
	else
		throw std::runtime_error{"Object texture path string empty"};

	return object;
}
