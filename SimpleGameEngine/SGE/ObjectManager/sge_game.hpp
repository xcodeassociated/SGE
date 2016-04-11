#ifndef SGE_GAME_HPP
#define SGE_GAME_HPP

namespace SGE
{
    class InputHandler;
    
	ObjectManager::Game::Game(ObjectManager* m):
		manager(m),
		limiter(new FpsLimiter())
	{
		this->limiter->init(60);
	}

	void ObjectManager::Game::run()
	{
		this->playing = true;
		while (this->playing)
		{
			this->limiter->begin();
			{
				this->draw();

                //SDL input processing
                (*(this->input_handler))();
    
                
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

	void ObjectManager::Game::stop()
	{
		this->playing = false;
	}

	void ObjectManager::Game::draw() {
		this->manager->renderer->render();
	}
    
    void ObjectManager::Game::setInputHandler(ObjectManager::InputHandler* e){
        (e != nullptr) ? this->input_handler = e : throw std::runtime_error("");
    }
}
#endif // !SGE_GAME_HPP
