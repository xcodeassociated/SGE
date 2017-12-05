#include "sge_game.hpp"
#include "sge_logic.hpp"
#include "sge_scene.hpp"
#include "sge_logic_bind.hpp"
#include "sge_object_manager.hpp"
#include "sge_renderer.hpp"
#include "sge_input_handler.hpp"
#include "sge_action_handler.hpp"
#include "sge_fps_limiter.hpp"
#include "sge_logger.hpp"

namespace SGE
{
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
