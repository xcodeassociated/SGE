#include "sge_game.hpp"
#include "sge_director.hpp"
#include "sge_logic_bind.hpp"
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
#include "tool/sge_input_handler.hpp"

#include <iostream>

namespace SGE
{
    std::shared_ptr<Logger> ObjectManager::logger = LoggerFactory::create_logger("ObjectManager");
    std::shared_ptr<LoggerError> ObjectManager::logger_err = LoggerFactory::create_logger_error("ObjectManager_ERROR");

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

		this->game = new Game(this, this->action_handler);

		this->input_handler = new InputHandler(this);
		this->game->setInputHandler(this->input_handler);
		return true;
	}

	bool ObjectManager::isOnScene()
	{
		return this->OnScene;
	}

	void ObjectManager::showScene(Scene* s)
	{
		this->currentScene = s;
		auto sceneObjectsIt = this->sceneObjects.find(s);

		if (sceneObjectsIt == this->sceneObjects.end())
            throw std::runtime_error("Scene not Loaded");

		s->BindObjects(&(*sceneObjectsIt).second);

		this->OnScene = true;

		this->window_manager->showWindow();

		this->renderer->initShader();

		this->renderer->spriteBatchInit();

		s->onDraw();

		this->game->run();
	}

	Level& ObjectManager::getSceneData(Scene* s)
	{
		return s->getLevel();
	}

	Camera2d* ObjectManager::getCamera()
	{
		return this->camera_handler->getCamera();
	}

	Game* Game::getGame()
	{
		static Game* game = new Game();
		return game;
	}

	void Game::mapAction(const InputBinder& bind)
	{
		this->input_handler->mapAction(bind);
	}

	void Game::unmapAction(const InputBinder& bind)
	{
		this->input_handler->unmapAction(bind);
	}

	void Game::finalize()
	{
		*logger << "ObjectManager Finalize method invoked" << std::endl;
 	}

	void Game::windowClosing()
	{
		this->window_manager->finalizeWindow();
        this->game->stop();
	}

	ActionHandler* Game::getActionHandler()
	{
		return this->action_handler;
	}

	Object* Game::getMouse()
	{
		return this->input_handler->getMouseHandler()->getMouseObject();
	}

	void Game::bindDirector(Director* director)
	{
		this->director = director;
		director->bindManager(this);
	}



    Game::Game(ObjectManager* m, ActionHandler* ah) :
            manager(m),
            limiter(new FpsLimiter()),
            action_handler(ah),
            logger(LoggerFactory::create_logger("Game"))
    {
        this->limiter->init(60);
    }

    //todo Reset limiter whenever scene is started
    void Game::run()
    {
        Logic::action_handler = this->manager->action_handler;
        this->playing = true;
        while (this->playing)
        {
            //On first iteration time is less than 10^10, but that may change with sceene swapping.
            this->limiter->begin();
            {
                this->performActions();
                this->performLogics();
                this->draw();

                this->input_handler->operator()();

                this->time += 0.01f;
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

    void Game::performActions(void) {
        this->action_handler->performAllActions();
    }

    void Game::performLogics(void)
    {
        auto& lVec = this->manager->currentScene->getLogics();

        LogicPriority objectCurrentLogicP = LogicPriority::None;
        LogicPriority nextLogicP = LogicPriority::None;

        for (auto it = lVec.begin(), end = lVec.end(); it != end; ++it)
        {
            nextLogicP = it->getLogic()->getPriority();

            if (nextLogicP <= objectCurrentLogicP) {
                if (it->getLogic()->getOn())
                    it->getLogic()->performLogic(it->getObject());
            }
        }
    }

    void Game::stop()
    {
        this->playing = false;
    }

    void Game::draw() {
        this->manager->renderer->render();
    }

    void Game::setInputHandler(InputHandler* e)
    {
        (e != nullptr) ? this->input_handler = e : throw std::runtime_error("Cannot set input_handler - passed null");
    }
}
