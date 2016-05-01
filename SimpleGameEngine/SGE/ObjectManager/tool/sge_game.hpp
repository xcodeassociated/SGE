#ifndef SGE_GAME_HPP
#define SGE_GAME_HPP

namespace SGE
{
    class InputHandler;
    
	ObjectManager::Game::Game(ObjectManager* m, ActionHandler* ah):
		manager(m),
		limiter(new FpsLimiter()),
        action_handler(ah)
	{
		this->limiter->init(60);
	}

	void ObjectManager::Game::run()
	{
		Logic::action_handler = this->manager->action_handler;
		this->playing = true;
		while (this->playing)
		{
			this->limiter->begin();
			{
				this->performLogics();
                this->performActions();
                
				this->draw();

                //SDL input processing
            //	( *(this->input_handler) )();
				this->input_handler->operator()();
                
				this->time += 0.01f;
			}
			this->fps = this->limiter->end();

			static int frameCounter = 0;
			frameCounter++;
			if (frameCounter == 100) {
				std::cout << "fps: " << this->fps << std::endl;
				frameCounter = 0;
			}
		}

	}
    
    void ObjectManager::Game::performActions(void){
        this->action_handler->performAllActions();
    }

	void ObjectManager::Game::performLogics(void)
	{
		auto lVec = this->manager->currentScene->getLogics();
        
        LogicPriority objectCurrentLogicP = LogicPriority::None;
        LogicPriority nextLogicP = LogicPriority::None;
        
		for(auto it = lVec.begin(), end = lVec.end(); it != end; ++it)
		{
            objectCurrentLogicP = it->getObject().getObject()->getLock();
            nextLogicP = it->getLogic().logic->getPriority();
            
            if (objectCurrentLogicP <= nextLogicP) {
                if(it->getLogic().logic->getOn())
                    it->getLogic().logic->performLogic(it->getObject());
            }
		}
	}

	void ObjectManager::Game::stop()
	{
		this->playing = false;
	}

	void ObjectManager::Game::draw() {
		this->manager->renderer->render();
	}
    
    void ObjectManager::Game::setInputHandler(ObjectManager::InputHandler* e)
    {
        (e != nullptr) ? this->input_handler = e : throw std::runtime_error("");
    }
}
#endif // !SGE_GAME_HPP
