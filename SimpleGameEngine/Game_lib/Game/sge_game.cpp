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
#include "sge_input_handler.hpp"

namespace SGE
{
    std::shared_ptr<Logger> Game::logger = LoggerFactory::create_logger("Game");
    std::shared_ptr<LoggerError> Game::logger_err = LoggerFactory::create_logger_error("Game_ERROR");

	bool Game::init(float fps)
	{
		std::pair<int, int> resolution = this->director->getResolution();

        this->action_handler = new ActionHandler;
        this->limiter = new FpsLimiter;
        this->limiter->init(fps);
		this->window_manager = new WindowManager(resolution, this);
		this->window_manager->createWindow();

		this->camera_handler = new CameraHandler(resolution);
		this->camera_handler->setPosition(this->camera_handler->getScreenToWorld(0, 0));
		this->camera_handler->setScale(.5f);

		this->renderer = new Renderer(resolution, this, this->window_manager, this->camera_handler);

		this->input_handler = new InputHandler(this);

		return true;
	}

	bool Game::isOnScene()
	{
		return this->OnScene;
	}

	void Game::showScene(Scene* s)
	{
		this->currentScene = s;

		this->OnScene = true;

        //TODO: this should be executed before - required if we want to swap scene
		this->window_manager->showWindow();
		this->renderer->initShader();
		this->renderer->spriteBatchInit();

		s->onDraw();

		this->run();
	}

	Level& Game::getSceneData(Scene* s)
	{
		return s->getLevel();
	}

	Camera2d* Game::getCamera()
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
		*logger << "Game Finalize method invoked" << std::endl;
 	}

	void Game::windowClosing()
	{
		this->window_manager->finalizeWindow();
        this->stop();
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
        director->bindGame(this);
	}

    Game::Game()
    {
    }

    //todo Reset limiter whenever scene is started
    void Game::run()
    {
        Logic::action_handler = this->action_handler;
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

    void Game::performActions(void)
	{
        this->action_handler->performAllActions();
    }

    void Game::performLogics(void)
    {
        auto& lVec = this->currentScene->getLogics();

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

    void Game::draw()
	{
        this->renderer->render();
    }

	Object* Game::textureObject(Object *object, std::string path)
	{
        // TODO: Check if file exists!

		if (!path.empty())
        {
            object->texture = this->rManager->getTexture(path.c_str());
            object->hasTexture = true;
        }
        else
			throw std::runtime_error{"Object texture path string empty"};
	}
}
